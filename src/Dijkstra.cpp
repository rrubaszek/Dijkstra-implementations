#include "Graph.hpp"
#include "Parse.hpp"
#include "Timer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

int main(int argc, char* argv[])
{
    std::unordered_map<std::string, std::string> args;

    if (argc < 6)
    {
        std::cerr << "Error: Too few arguments" << std::endl;
    }

    for (int i = 1; i < argc; i++) 
    {
        if (i + 1 < argc) 
        {
            args[argv[i]] = argv[i + 1];
            i++;
        } 
        else 
        {
            std::cerr << "Error: Missing value for flag " << argv[i] << std::endl;
            return 1;
        }
    }

    Parse parser;
    Graph graph;
    std::string flag, res_file, command;
    std::vector<int> sources; // for single source, all dest
    std::vector<std::pair<int, int>> sources_dest; // for specific source, specific dest

    if (args.count("-d"))
    {
        // find data file path and build graph
        auto path = args.at("-d");
        std::string filename = parser.find_file(path);
        command = parser.parse_data(filename, graph);
    } 

    if (args.count("-ss"))
    {
        // find .ss input file and build vector<int>
        std::string filename = parser.find_file(args.at("-ss"));
        res_file = args.at("-oss");
        sources = parser.parse_input(filename);
        flag = "-ss";
    }
    else if (args.count("-p2p"))
    {
        // find .p2p input file and build vector<pair<int,int>>
        std::string filename = parser.find_file(args.at("-p2p"));
        res_file = args.at("-op2p");
        sources_dest = parser.parse_input_pairs(filename);
        flag = "-p2p";
    }

    std::ofstream out_file;
    out_file.open(res_file, std::ios::out);
    if (!out_file.is_open()) 
    {
        std::cerr << "Error opening file for writing: " << res_file << std::endl;
        return 1;
    }
    
    out_file << "p " << argv[0] << " " << command << "\n";
    out_file << "c wyniki testu dla sieci zadanej w pliku: " << argv[4] << "\nc i pliku ze zrodlami: " << argv[6] << "\n";
    out_file << "--------------\n";
    std::pair<long long, long long> weights = graph.get_min_max_weight();
    out_file << "c siec sklada sie z " << graph.get_nodes() << " wierzcholkow, " << graph.get_edges() << " lukow,\nc koszty naleza do przedzialu [" << weights.first << ", " << weights.second << "]\n";
    out_file << "g " << graph.get_nodes() << " " << graph.get_edges() << " " << weights.first << " " << weights.second << "\n";

    std::vector<long long> vec;
    std::chrono::duration<double> time;
    Timer t;
    if (flag == "-ss")
    {
        for (int i : sources)
        {
            t.reset();
            vec = graph.dijkstra(i);
            time += t.time_elapsed();
        }

        time = time / sources.size();

        out_file << "c sredni czas wyznaczenia najkrotszych sciezek miedzy zrodlem\nc a wszystkimi wierzcholkami wynosi (s):\nt " << time.count();
    }
    else if (flag == "-p2p")
    {
        for (const auto& p : sources_dest)
        {
            t.reset();
            vec = graph.dijkstra(p.first);
            time += t.time_elapsed();
            out_file << "d " << p.first << " " << p.second << " " << vec.at(p.second) << "\n";
        }

        time = time / sources_dest.size();

        out_file << "c sredni czas wyznaczenia najkrotszych sciezek miedzy parami (s, t) wynosi (s):\nt " << time.count();
    } 
    
    out_file.close();

    std::cout << time.count() << std::endl;

    return 0;
}