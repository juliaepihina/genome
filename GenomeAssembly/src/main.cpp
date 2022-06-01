// main.cpp
// Application entry point
#include "../include/DeBruijnGraph.h"
#include <algorithm>
#include <fstream>

int main(int argc, char** argv)
{
    // argv[1] - reads input file name
    // argv[2] - result file name

    vector<string> Reads;

    /*cout << "\n[GENOME ASSEMBLER]\n";
    cout << "\n[Info] Value of K ";
    cout << "\n[Info] K is best chosen to be 2 more than the maximum overlap of the reads for this program.";
    cout << "\n[Info] Also, K should be more than 2 and atleast equal to the length of the shortest read.";
    cout << "\n\n[Input] Enter K: ";*/
    int k;
    //cin >> k;
    
   /* cout << "\n[Input] Enter number of reads: ";*/
    int count = 0;
    //cin >> count;

    /*cout << "\n[Input] Please enter the reads: \n";*/
    
    int min_readsize = 0;
    vector<int> read_sizes;
    
    ifstream file1(argv[1]);
    
    while(!file1.eof()) {
        string read;
        file1 >> read;

        if(read == "")
            continue;

        Reads.push_back(read);
        read_sizes.push_back(read.length());
        count++;
    }

    file1.close();
    
    k = 3;

    min_readsize = *min_element(read_sizes.begin(), read_sizes.end());

    //cout << min_readsize << endl;

    // The value of k cannot be more than the minimum read size
    while (k > min_readsize || k < 2)
    {
        cout << "\n[ERROR!] Value of K cannot be more than the shortest read's length, and should be atleast 2." << endl;
        exit(-1);
    }

    string orign = "", orign2 = "", orign3 = "";
    // We shall take 3 observations (of output string) and display the one that recurs

    KMerifier kmf = KMerifier(k, Reads);

    // The DeBruijnGraph takes a KMerifier object in its constructor
    DeBruijnGraph dbg = DeBruijnGraph(kmf);

    // Get the original string by performing an Eulerian walk of the graph
    orign = dbg.DoEulerianWalk();

    if (k + 1 <= min_readsize)
    {
        KMerifier kmf2 = KMerifier(k + 1, Reads);
        DeBruijnGraph dbg2 = DeBruijnGraph(kmf2);

        orign2 = dbg2.DoEulerianWalk();
    }

    if (k - 1 >= 2)
    {
        KMerifier kmf3 = KMerifier(k - 1, Reads);
        DeBruijnGraph dbg3 = DeBruijnGraph(kmf3);

        orign3 = dbg3.DoEulerianWalk();
    }

    // Now we need to find the shortest length superstring
    vector<string> origns = {orign, orign2, orign3}; // genome length can be very large!

    int min_out_size_ind = 0;

    for (int i = 0; i < 3; i++)
    {
        if (origns[i].length() < origns[min_out_size_ind].length() && origns[i].length() > 0)
        {
            min_out_size_ind = i;
        }
    }

    ofstream fileo(argv[2]);

    fileo << origns[min_out_size_ind] << endl;

    fileo.close();

    //cout << "\n[Output] Possible shortest-length original superstring: \n" << origns[min_out_size_ind] << endl;
    //cout << "\n\n[Output] All generated superstrings: \n" << origns[0] << "\n" << origns[1] << "\n" << origns[2] << endl << endl; 

    return 0;
}
