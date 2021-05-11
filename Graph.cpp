
using namespace std;

#define RESET   "\033[0m"
// #define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
// #define WHITE   "\033[37m"      /* White */
// #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
// #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


map <int , string> colorNames; // map for terminal colors - used for printing node colors 



template <class T>
void printVector_set( vector<vector<T>> set){
    
    for(auto it : set){
        cout<<"{";

        for(T K:it ){
            cout<<K;
            
        }
        cout<<"}"<<endl;


    }

}


template <class T>
void printVector( vector<T> set){
        cout<<"{";
    
    for(auto it : set){

         cout<<it;
    }
        cout<<"}"<<endl;


}





template <class T>
Graph<T>::Graph(){

    // // initalizes a global bap variable "colorList" to be used to print terminal colors in functions 
    // string arr[12] = { RED,GREEN, YELLOW,BLUE,MAGENTA,CYAN, BOLDRED,BOLDGREEN,BOLDYELLOW,BOLDBLUE, BOLDMAGENTA,BOLDCYAN };
    //  for(int i =0; i< 12;i++){
    //     colorNames.emplace(i, arr[i] );
    // }

}



template <class T>
void Graph <T>::addVertex(T vertex){
 
    //TODO: copy and paste this into your lab 11

    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        // if vertex is found
        if (it->first == vertex) {
			
            std::cout << RED << "Vertex " << vertex << " is already in the graph." << RESET << std::endl;
            return; // leave
        }
    }



    // inserts that node value with no neighbors ( empty vector)
    vertices.emplace(vertex, vector<T>());
}

// // add an undirected edge to the graph so add to both adjacency lists 
template <class T>
void Graph<T>::addEdge(T vertex, T vertex2 ){
    bool isPath1 = false, isPath2= false ; 
    for( auto it = vertices.begin(); it != vertices.end(); it++){

        if(it-> first == vertex){
            // searches through the list of neighbor nodes
            for( int i = 0; i < it->second.size() ;i++){
                if(it ->second[i] == vertex2){
                    isPath1= true;
                }
            }

            if(!isPath1){
                it->second.push_back(vertex2);
            }
        }

         // if the graph is undirected then add an edge 
        if(it-> first == vertex2 ){
            for( int i = 0; i < it->second.size() ;i++){
                // cout<<it->second[i]<<endl;
                if(it ->second[i] == vertex){
                    isPath1= true;
                }
            }

            if( isPath1 == false && isPath2 == false ){
                it->second.push_back(vertex);
            }
        }
    }
}


// // prints the adjacency list of each vertex, to show the structure
template <class T>
void Graph<T>::print(){
    for( auto it = vertices.begin(); it != vertices.end(); it++){
        cout<<"V= "<<it->first;
        cout<<" {";

        for( int i = 0; i < it->second.size() ;i++){
            cout<<it->second[i] <<", ";
        }
        cout<<"}"<<endl;
    }

}  

// GreedyColoring(Graph G(V, E)):
// 	for all v ∈ V(G):
// 		color(v) ←  -1
// 	for all v ∈ V(G) in order:
// 		isColored (1… ∆(G) + 1) ← false // initiaizing SOMETHING to false for every vertex in the graph 
// 		for all u ∈ N(v) where color(u) ≠ −1 // for all neighbors where it is marked 
// 			isColored (color(u))  ← true // if is colored then indicate it 
// 		for k = 1… ∆(G) + 1: 
// 			if isColored (k) = false:
// 				color(v) ← k
// 				break
// 	k ← max(color(1...n))
// // return k // returns the number of colors used 

template <class T>
void  Graph<T>::greedyColor(){
    auto it = vertices.begin();
    greedyColor(it->first);

}


template <class T>
void  Graph<T>::greedyColor(T vertex){
    map< T , int > coloredGraph; // stores the final colored graph
    list <int> totalColors;
    int color = 1 ;

    for(  T i : vertices[vertex]){
        coloredGraph.emplace(i, -1);
    }

    for( auto it = vertices.begin(); it != vertices.end(); it++){
        list <int> availableColors = totalColors; // use overloaded = to copy all of the colors in the graph is later modified 

        for( auto j = 0; j < it->second.size() ;j++){

             //for every colored neighbor of u 
            if(coloredGraph[it->second[j]] > 0 ){ 
                // for every colored neighbor take out that color from the availableColors list 
                availableColors.remove(coloredGraph[it->second[j]]);

            }
            
            // current "hub" uses all available colors... assign current node to a new color 
            if(availableColors.empty()){
                totalColors.push_front(color); // add color to our list of colors
                coloredGraph[it->first] = color;
                color++;

            // there exists an available color to assign the current node to... i.e select from beg of list 
            }else{ 
                int color = availableColors.front();
                coloredGraph[it->first] = color;

             }
        }
    }

    printf("\n\nFINAL COLORING\n");

    for( auto i = vertices.begin(); i != vertices.end(); i++){
        int color = coloredGraph[i->first];
        cout<<"node=" <<i->first <<" color= " << colorNames[color]<< coloredGraph[i->first] <<RESET<<endl;
    }
    printf("There were %lu colors used to color the graph \n\n", totalColors.size());

}



// passing in a graph that needs the correct edges added but already has the verticies
template <class T>
Graph<T> Graph<T>::makeSubgraph( Graph  & newGraph ){
    // it thru verticies, if the verticies math then add all of the neighbors 
    
    auto graphIt = newGraph.vertices.begin();

    for (auto it = vertices.begin(); it != vertices.end(); it++) {
    //     // if vertex is found and iterate thru neighbors... add edges 

        if(graphIt != newGraph.vertices.end()){
            //  graphIt++;

        
            if (it->first == graphIt->first) {
                T node1 = it->first;

                for( auto i : vertices [it->first]){
                    T node2 = i;

                    if( newGraph.vertices.count(i) > 0){ // both nodes exist in the newGraph and the edges between them need to be added 
                        newGraph.addEdge(node1 , node2);
                    }
                }

            
            }
        }
        if(graphIt != newGraph.vertices.end()){
             graphIt++;

        }



    }


    newGraph.print();
    return newGraph;

}


// pass in 2^n and the graph array to generate all SUBGRAPHS
template <class T>
void Graph<T>:: genSubgraphs(int n , Graph arr[]){


    int totalBits =log2(n);
    // cout<<"n="<<n<<endl;
    // cout<<"totalBits"<<totalBits<<endl;
    int bitNum = 1;
    int arrIndex =0;

    arr[0] = Graph();

    queue<string> qu;
    qu.push("1");
    while(n != 0){
        string s1 = qu.front();
        qu.pop();

        if( ceil(log2(qu.size()+1)) == floor(log2(qu.size()+1)) ){
            bitNum ++;
        }
     

        Graph <T> temp;   
        string bitStr = s1;
        while(bitStr.length() < totalBits){
            bitStr = "0" + bitStr;
        }

        auto it = vertices.begin(); 
        for(int i =0; i < vertices.size()  ;i++){

            if(bitStr[i] =='1' ){
                temp.addVertex(it->first);
            }
            if(it != vertices.end()){
                it++;
            }

        }
        
        makeSubgraph(temp);
        arr[arrIndex ++] = temp;

        string s2 = s1;
        qu.push(s1 + "0");
        qu.push(s1 + "1");
        n--;
    }



//         cout <<"final"<<endl;

//     for(int i =0 ;i<pow(2, vertices .size());  i++){
//         arr[i].print();
//         cout<<endl;
//     }
}


// given a graph and a vertex will return the degree 
template <class T>
int Graph<T>::degree(Graph current, T vertex){

    // todo: double check 
     if(current.vertices.size() ==0){
        // cout<<"base case"<<endl;

        return 0;
    }

    for (auto it = current.vertices.begin(); it != current.vertices.end(); it++) {
       if(it->first == vertex){
           cout<<it->second.size()<<endl;
           return it->second.size();

       }
    }
   
    return -1;
}


// finds first instance for the smallMis graph 
// template <class T>
// degreePair<T>  Graph<T>::findDegree(Graph current){
//     degreePair <T> set;
//     int index=0;
//     for (auto it = current.vertices.begin(); it != current.vertices.end(); it++ ,index++) {
//         int degreeNum = degree( current , it->first) ;

//         if( degreeNum>= 3 || degreeNum== 1 || degreeNum== 0){
//             set.vertexValue = it->first;
//             set.degree= degreeNum;
//         }
//     } 

//     return set; // there is not a case that satsifies the the first if statements in smallMIS 
// }


template <class T>
vector <T> Graph<T>::setUnion( vector <T> set1 , vector<T>  set2){
    // cout<<"here1:"<<endl;
    vector<T> v( set1.size() +set2.size());  

    auto it= set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), v.begin());
    v.resize(it-v.begin());   

    return v;  
}

template <class T>
vector <T> Graph<T>::symDiff( vector <T> set1 , vector<T>  set2){
    vector<T> v( set1.size() +set2.size()  );  
    auto it =  set_symmetric_difference (set1.begin(), set1.end(), set2.begin(), set2.end(), v.begin());
    v.resize(it-v.begin());   

    return v;   
}


// given a graph and two nodes are the two nodes ever connected i.e neighbors 
template <class T>
bool Graph<T>::areConnected(Graph subGraph, T node1 , T node2){
    for(auto i : subGraph.vertices [node1]){
            // cout<< "i= "<<i <<" node1 = "<<node1 <<" node2="<<node2<<endl;
        if(i == node2){
            // cout<<"correct neighbor"<<endl;
            return true;

        }        

    }
    // cout<<"NOT neighbor"<<endl;
    return false;   
}


// find all independet sets and then keep the "largest ones" and return for the color function to iterate 

template <class T>
vector< vector<T> > Graph<T>::checkIndependentSets(Graph subGraph, vector< vector<T>> currentSet){
    vector< vector<T>> indep_Sets ;
    // cout<<"checkIndependentSets"<<endl;
    // printVector_set(currentSet);

    int maxSizeMIS =0;

    // checks if there are two adjacent edges 
    // iterate thru the sets of current sets 
    for(auto i : currentSet){
        bool addList = true;

        for(T node1:i ){
            for(T node2:i ){
                if(areConnected(subGraph , node1 , node2) == true){ // tests to see if two neighbors are adjacent
                    addList = false; // the first instance that it is stops looking at this set 
                    break;
                }
            }

        }

        //measures the max Size of the independent set
        if(addList == true  ){
            // indep_Sets.push_back(i);
            if(i.size() > maxSizeMIS){
                maxSizeMIS = i.size();
            }
        }

    }



    // does the whole thing again but only adds the sets of the largest maxsize to return 
    for(auto i : currentSet){
        bool addList = true;

        for(T node1:i ){
            for(T node2:i ){
                if(areConnected(subGraph , node1 , node2) == true){
                    addList = false;
                    break;
                }
            }

        }
        if(addList == true  &&  i.size() == maxSizeMIS){
            indep_Sets.push_back(i);
           
        }

    }

    return indep_Sets;

}



// gen sets given a vector of verticies 
template <class T>
void Graph<T>:: genSets(int n , vector<vector<T>> & sets){
    int totalBits =log2(n);
    int bitNum = 1;
    int arrIndex =0;

    queue<string> qu;
    qu.push("1");
    while(n != 0){
        string s1 = qu.front();
        qu.pop();

        if( ceil(log2(qu.size()+1)) == floor(log2(qu.size()+1)) ){
            bitNum ++;
        }
     

        vector <T> temp;   
        string bitStr = s1;
        while(bitStr.length() < totalBits){
            bitStr = "0" + bitStr;
        }

        auto it = vertices.begin(); 
        // cout <<"\nhere"<< bitStr<<endl;
        for(int i =0; i < vertices.size()  ;i++){

            if(bitStr[i] =='1' ){
                temp.push_back(it->first);
            }
            if(it != vertices.end()){
                it++;
            }

        }
        
        sets.push_back(temp);


        string s2 = s1;
        qu.push(s1 + "0");
        qu.push(s1 + "1");
        n--;
    }

}

//given a graph: will return all verticies in the set
template <class T>
vector<T> Graph<T>:: get_verticesSet(Graph current){
    vector <T> S;

    for (auto it = current.vertices.begin(); it != current.vertices.end(); it++) {
        S.push_back(it->first);
    }
    return S;

}

// given a vector with verticies, will determine its binary representation 
template <class T>
int Graph<T>:: get_binary(vector<T> current){
    string bin;

    for(int i =0;i< vertices.size() ;i++){ // need all the verticies in the calling graph for chrom number
        bin+="0";
    } 

    int index =0;
    for(auto i=vertices.begin(); i != vertices.end()  ;i++ ){
        // cout<<"index"<<index<<endl;
        for(auto vertex : current){ // iterate on all verticies in the current graph to see if also in original graph

            if(vertex == i ->first){
                bin[index] = '1';
                // cout<<"vertex "<<vertex <<" "<<i->first<< " "<< endl;
                // cout<<"index"<<index<<endl;
            }
        }
        index++;
    } 
    
    index--;
    int binaryNum =0;
    // cout<<"binary string"<<bin<<endl;
    for(int i = 0 ; i<vertices.size()  ;i++){
        if(bin[i] == '1'){
            binaryNum += pow(2, index );
        }
        index--;

    }

    // cout<<"binary number is "<<binaryNum<<endl;
    return binaryNum;

}

// takes info from a given graph (will be a subgraph) and sends the info to SMALL MIS in the correct format
template <class T>
void Graph<T>::prepMIS(Graph current ,  vector <vector<T>> & set_MIS){
 
    // current.print();


    // 2^n set of verticies and go through and make sure they are not connected by an edge 
    int graphSize = pow(2,current.vertices.size());
    genSets( graphSize, set_MIS);


    // cout<<"printing the gen sets"<<endl;
    // printVector_set(set_MIS);

    // // 3. weed out non-independent sets and return the valid ones 
    set_MIS = checkIndependentSets(current ,  set_MIS);

    // cout<<"printing the weed out gen sets"<<endl;
    // printVector_set(set_MIS);
    


     
// 2. generate 2^n  sets of verticies  
// 3. Check if independent set ... aka set DN have two adjacent verticies 
// - do them all first . Find Max then add all those to the set 
// - keep track of all the “maximum” size of each independent set … 

// - iterate in the for loop for this line  X[S] = min(X[S], X[S \ I] + 1) 


// smallMIS(current, set_MIS, S , I , S.size()-1  );
// find all independet sets and then keep the "largest ones" and return for the color function to iterate 
    

}


template <class T>
void Graph<T>::color(){



    int arrSize = pow(2, vertices.size());
    Graph<T> subGraphs [arrSize]; 
    genSubgraphs(arrSize, subGraphs);

    int X [arrSize];
    for(int i =0 ; i< arrSize -1 ; i++){
        X[i] = arrSize;
    }


    for(int S =0 ; S < arrSize -1 ; S++){
        // call prepMIS on every graph which generates all information for independet sets
        vector <vector<T> > MIS;
        prepMIS(subGraphs[ arrSize -2 ] , MIS);

        // for every maximum independent set found from this subgraph
        for(auto vectorIT : MIS){
            for(T vertex :vectorIT ){ // j is type T so we can print 

                vector<T> S_I = get_verticesSet(subGraphs[S]); 
                S_I = symDiff(S_I, vectorIT);
                // printVector(S_I);
                // get_binary(S_I);

                X[S] = min( X[S] , X[ get_binary(S_I)]+1 );
                // cout<<X[S]<<endl;
                 // psuedocode
                // X[S] = min(X[S], X[S \ I] + 1

            }
        }

    }
    subGraphs[arrSize-2].print();
    cout<<"The chromatic number of the graph is "<< X[arrSize-2]<<endl;


}






// ______________________

// alg 1
// todo return a stack 

// template <class T>
// void  Graph<T>::smallMIS(Graph cur , vector <vector<T>>  & set_MIS ,  vector <T> S , vector<T> I , int k ){


//     degreePair <T> degreeV = findDegree(cur); // finds first instance that satisfies the degree of the verticie

//     if (S.size() == 0 or k== 0) {
//         cout<<"Base case"<<endl;
//         // return process i 
//         set_MIS.push_back(I);




//     }else if(degreeV.degree >=3  ){ //there exists v ∈ S with deg(v, S) ≥ 3
//         cout<<" case 2: degree3 "<<endl;
//         vector <T> vertexV= {degreeV.vertexValue} ; // {v} 
//         smallMIS ( cur,set_MIS, symDiff(S,vertexV ) , I , k);
//         smallMIS ( cur, set_MIS, symDiff(S, cur.vertices.find(degreeV.vertexValue)->second ) , setUnion(I , vertexV ) , k-1);
        
//         // psudeocode
//         // smallMIS (S \ {v}, I, k);
//         // smallMIS (S \ N(v), I ∪ {v}, k − 1); }

//     }else if(degreeV.degree ==1 ){//there exists v ∈ S with deg(v, S) = 1
//         cout<<" case 3:degree1 "<<endl;

//         //TODO: make func that returns the first neighbor given a vertex
//         T u = cur.vertices.begin()->second[0]; // finding the first neighbor of V 
//         vector <T> vertexV= {degreeV.vertexValue} ;// {v} 
//         vector <T> vertexU= {u} ;// {u} 


//         // smallMIS ( cur, set_MIS,symDiff(S, cur.vertices.find(u)->second ), setUnion(I , vertexU ) , k-1);
//         // smallMIS ( cur,set_MIS, symDiff(S, cur.vertices.find(degreeV.vertexValue)->second ) , setUnion(I , vertexV ) , k-1);
       
//         // psudeocode
//         // let u be the neighbor of v;
//         // smallMIS (S \ N(u), I ∪ {u}, k − 1);
//         //  smallMIS (S \ N(v), I ∪ {v}, k − 1);
        
//     }else if( degreeV.degree ==0 ){//there exists v ∈ S with deg(v, S) = 0
//         cout<<" case 4: degree 0 "<<endl;
//         vector <T> vertexV= {degreeV.vertexValue} ; // {v} 
//         smallMIS ( cur, set_MIS, symDiff(S,vertexV)  , setUnion(I , vertexV ) , k-1);
        
//         // psudeocode
//         // smallMIS (S \ {v}, I ∪ {v}, k − 1);


//     // TODO: talk about this case 
//     }else{ //some cycle in S is not a triangle or k ≥ |S|/3
//         cout<<" case 5: triangle"<<endl;
//         // let u, v, and w be adjacent degree-two vertices, such that (if possible) u and w are nonadjacent; smallMIS (S \ N(u), I ∪ {u}, k − 1);
//         // smallMIS (S \ N(v), I ∪ {v}, k − 1);
//         // smallMIS (S \ ({u} ∪ N(w)), I ∪ {w}, k − 1);


//     }

// }

