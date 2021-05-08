
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
Graph<T>::Graph(){

    // initalizes a global bap variable "colorList" to be used to print terminal colors in functions 
    string arr[12] = { RED,GREEN, YELLOW,BLUE,MAGENTA,CYAN, BOLDRED,BOLDGREEN,BOLDYELLOW,BOLDBLUE, BOLDMAGENTA,BOLDCYAN };
     for(int i =0; i< 12;i++){
        colorNames.emplace(i, arr[i] );
    }

}

template <class T>
void Graph <T>::addVertex(T vertex){

    // checks if the vertex is already in the graph 
    for(  T i : vertices[vertex]){
        if(i == vertex){
            // printf("The Verticie '%d'  is already in the graph\n", vertex);
            cout<<"The Verticie "<< vertex<< "is already in the graph"<<endl;
            return;
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
void  Graph<T>::colorGraph(){
    auto it = vertices.begin();
    colorGraph(it->first);

}


template <class T>
void  Graph<T>::colorGraph(T vertex){
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


template <class T>
void Graph<T>::findChromatic(){

    //make a graph of 2^n size and store in a list 
    // 1. put subgraph into vector .. i.e their verticies? Should we have map< X(G) , Graph> 
            // make helper function which takes list of verticies ?? a vector?
        // 1a. make a GRAPH using these verticies (make a helper function which given a graph returns the correct subgraph of the original )
                // send this graph into step 2
        //2. test subgraph for the chromatic number (alg2) int X(G) = algorithm2(Graph G ) // returns an int
            // map.emplace(X(G) , SUBGRAPH G )





    // illistrates how to get all permutations of a given number list ... use for generated 

    vector<T> v;      
    for(int i=0;i<vertices.size();i++){
        v.push_back(i);
    }

    do{
        cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<endl;
    }while(next_permutation(v.begin(),v.end()));
    


}



