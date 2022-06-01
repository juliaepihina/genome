#include "sequencing.h"
#include "assembly.h"

#include <algorithm>
#include <fstream>

int main(int argc, char* argv[]) {
    data input = data();
    vector<vector<int>> graph;
    vector<string> reads_vec;
    int graph_size = 0;

    if (argc == 2) {
        if (string(argv[1]) == "-h") {
            print_help();
        }
        else if (string(argv[1]) == "-ar") {
            auto_remove();
        }/*else if(string(argv[2]) == "-r") {
            input.is_rand = true;
            input.source_dna = "source.txt";
            input.sequence_length = atoi(argv[2]);
        } *//*else {
            print_help();
            exit(0);
        }*/
    }
    else if (argc == 10) {
        parse_input(argc, argv, input);
        if (input.is_rand) {
            generate_sequence(input.sequence_length, input.source_dna);
        }
        reads_create(input, graph_size, reads_vec);
        fill_graph(input, graph_size, graph);
        save_graph(graph_size, graph, input.graph_filename);
        system((input.tested_program + " -g " + input.graph_filename + " -o " + input.output_filename).c_str());
        build_dna(input.output_filename, input.result_dna, graph_size, reads_vec, graph);
        system((input.meter_program + " " + input.source_dna + " " + input.result_dna).c_str());
    }
    else {
        int minr, maxr, len;
        cout << "Length: ";
        cin >> len;
        cout << "Reads' min length: ";
        cin >> minr;
        cout << "Reads' max length: ";
        cin >> maxr;

        input.is_rand = true;
        input.source_dna = "source.txt";

        string alg2 = "./GA.exe";
        string source_reads = "reads.txt";
        string result2 = "result2.txt";

        input.sequence_length = len;
        input.min_reads_length = minr;
        input.max_reads_length = maxr;

        if (input.max_reads_length < input.min_reads_length ||
            input.min_reads_length < 1 ||
            input.max_reads_length < 1) {
            cout << "bad values" << endl;
            exit(0);
        }

        input.tested_program = string("./solver");
        input.meter_program = string("./meter");

        input.reads_filename = "reads.txt";
        input.graph_filename = "graph.txt";
        input.output_filename = "algo_output.txt";
        input.result_dna = "result.txt";

        generate_sequence(input.sequence_length, input.source_dna);
        reads_create(input, graph_size, reads_vec);
        fill_graph(input, graph_size, graph);
        save_graph(graph_size, graph, input.graph_filename);

        cout << "Algorithm #1 calculating..." << endl;
        system((input.tested_program + " -g " + input.graph_filename + " -o " + input.output_filename).c_str());
        build_dna(input.output_filename, input.result_dna, graph_size, reads_vec, graph);

        cout << "Algorithm #2 calculating..." << endl;
        system((alg2 + " " + source_reads + " " + result2).c_str());


        //cout << "Alg #1 result: ";    
        system((input.meter_program + " " + input.source_dna + " " + input.result_dna + " " + input.result_dna + "1").c_str());
        //cout << endl << "Alg #2 result: ";
        system((input.meter_program + " " + input.source_dna + " " + result2 + " " + result2 + "1").c_str());
        cout << endl;

        //system((input.meter_program + source_reads + " " + result2).c_str());

        ifstream res1(input.result_dna + "1");
        ifstream res2(result2 + "1");

        //string res1s, res2s;

        string res1s{ istreambuf_iterator<char>(res1), istreambuf_iterator<char>() };
        string res2s{ istreambuf_iterator<char>(res2), istreambuf_iterator<char>() };

        //res1 >> res1s;
        //res2 >> res2s;

        cout << res1s << endl << res2s << endl;

        res1.close();
        res2.close();

        size_t n1 = std::count(res1s.begin(), res1s.end(), ' ');
        size_t n2 = std::count(res2s.begin(), res2s.end(), ' ');

        cout << "First alg count of substrings: " << n1 << endl;
        cout << "Second alg count of substrings: " << n2 << endl;

        /*else if (argc == 10) {
            parse_input(argc, argv, input);
            if (input.is_rand) {
                generate_sequence(input.sequence_length, input.source_dna);
            }
            reads_create(input, graph_size, reads_vec);
            fill_graph(input, graph_size, graph);
            save_graph(graph_size, graph, input.graph_filename);
            system((input.tested_program + " -g " + input.graph_filename + " -o " + input.output_filename).c_str());
            build_dna(input.output_filename, input.result_dna, graph_size, reads_vec, graph);
            system((input.meter_program + " " + input.source_dna + " " + input.result_dna).c_str());
        } else {
            cout << "bad input in tester" << endl;
            print_help();
        }*/
    }


}

    

   
