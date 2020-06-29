/************************************************************************/
/* $Id: MainP.cpp 65 2010-09-08 06:48:36Z yan.qi.asu $                                                                 */
/************************************************************************/

#include <limits>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "GraphElements.h"
#include "Graph.h"
#include "DijkstraShortestPathAlg.h"
#include "YenTopKShortestPathsAlg.h"
#include <Rcpp.h>

// [[Rcpp::plugins("cpp11")]]

using namespace std;


// Roxygen comments go here
// [[Rcpp::export(name = ".k_shortest_paths_Cpp")]]
Rcpp::List k_shortest_paths_Cpp(Rcpp::DataFrame graph_df,
                                Rcpp::IntegerVector start_vertex,
                                Rcpp::IntegerVector end_vertex,
                                Rcpp::IntegerVector k,
                                Rcpp::IntegerVector vertex_num,
                                bool verbose = false)
{
	int start_vertex_ = Rcpp::as<int>(start_vertex);
	int end_vertex_ = Rcpp::as<int>(end_vertex);
	int k_ = Rcpp::as<int>(k);

	// Printing input
	if (verbose == true) {
		Rcpp::Rcout << "Route Start: " << start_vertex << std::endl;
		Rcpp::Rcout << "Route End: " << end_vertex << std::endl;
	}

	Graph my_graph(vertex_num, graph_df);


  BaseVertex* start_v = my_graph.get_vertex(start_vertex_);
  BaseVertex* end_v = my_graph.get_vertex(end_vertex_);

	YenTopKShortestPathsAlg yenAlg(my_graph,
                                 start_v,
                                 end_v);

	int i = 0;
	vector<int> path_vec;
	vector<vector<int> > results;
	BasePath* path = 0;
	while(yenAlg.has_next() && i < k_)
	{
		++i;
	  path = yenAlg.next();
		path_vec = path->PathVector();
		results.push_back((path_vec));

		if (verbose == true) {
			path->PrintOut(Rcpp::Rcout);
		}
	}
	delete path;

	return(Rcpp::wrap(results));
}
