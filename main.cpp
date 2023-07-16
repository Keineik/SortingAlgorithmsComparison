//#include "func.h"
#include "sort.cpp"
#include <iomanip>

void sorting_by_comp(string sortName, int *arr, int n, long long &comp){
    comp = 0;
    if (sortName == "bubble-sort"){
        return;
    }
    else if (sortName == "insertion-sort"){
        return;
    }
    else if (sortName == "shaker-sort"){
        return;
    }
    else if (sortName == "selection-sort"){
        return;
    }
    else if (sortName == "heap-sort"){
        heapSortVerComp(arr, n, comp);
        return;
    }
    else if (sortName == "quick-sort"){
        quickSortVerComp(arr, 0, n - 1, comp);
        return;
    }
    else if (sortName == "merge-sort"){
        mergeSortVerComp(arr, 0, n - 1, comp);
        return;
    }
    else if (sortName == "radix-sort"){
        return;
    }
    else if (sortName == "counting-sort"){
        return;
    }  
    else if (sortName == "shell-sort"){
        return;
    }
    else if (sortName == "flash-sort"){
        flashSortVerComp(arr, n, comp);
        return;
    }
}

void sorting_by_time(string sortName, int *arr, int n, double &time){
    if (sortName == "bubble-sort"){
        return;
    }
    else if (sortName == "insertion-sort"){
        return;
    }
    else if (sortName == "shaker-sort"){
        return;
    }
    else if (sortName == "selection-sort"){
        return;
    }
    else if (sortName == "heap-sort"){
        heapSortVerTime(arr, n, time);
        return;
    }
    else if (sortName == "quick-sort"){
        quickSortVerTime(arr, 0, n - 1, time);
        return;
    }
    else if (sortName == "merge-sort"){
        mergeSortVerTime(arr, 0, n - 1, time);
        return;
    }
    else if (sortName == "radix-sort"){
        return;
    }
    else if (sortName == "counting-sort"){
        return;
    }  
    else if (sortName == "shell-sort"){
        return;
    }
    else if (sortName == "flash-sort"){
        flashSortVerTime(arr, n, time);
        return;
    }
}

void algoOutput(string output, long long comp, double time, string order =""){
    if (order != "") cout << "Input order: " << order << endl;
    cout << "-------------------------" << endl;
    if (output == "-time")
        cout << "Running time: " << time << endl;
    else if (output == "-comp")
        cout << "Comparisons: " << comp << endl;
    else if (output == "-both")
        cout << "Running time: " << time << endl
             << "Comparisons: " << comp << endl;
    cout << endl;
}

void compOutput(string output, long long comp1, long long comp2, double time1, double time2){
    cout << "-------------------------" << endl;
    cout << "Running time: " << time1 << " | " << time2 << endl
         << "Comparisons: " << comp1 << " | " << comp2 << endl;
    cout << endl;
}

void readFile(string filename, int *&arr, int &n, int type = 1){
    delete[] arr;
    ifstream ifs(filename);
    if (!ifs) return;
    if (type)
        ifs >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++) ifs >> arr[i];
    ifs.close();
}

void writeFile(string filename, int *arr, int n){
    ofstream ofs(filename);
    ofs << n << endl;
    for (int i = 0; i < n; i++)
        ofs << arr[i] << " ";
    ofs.close();
}

int main(int argc, char *argv[]){
    if (string(argv[1]) == "-a"){
        cout << "ALGORITHM MODE" << endl;
        cout << "Algorithm: " << argv[2] << endl;
        int n, *arr;
        long long comp = 0;
        double time = 1;

        if (string(argv[3]).find(".txt") != -1){
            readFile(string(argv[3]), arr, n);
            cout << "Input file: " << argv[3] << endl;
            cout << "Input size: " << n << endl;
            if (string(argv[argc - 1]) == "-time")
                sorting_by_time(string(argv[2]), arr, n, time);
            else if (string(argv[argc - 1]) == "-comp")
                sorting_by_comp(string(argv[2]), arr, n, comp);
            else {
                sorting_by_time(string(argv[2]), arr, n, time);
                readFile(string(argv[3]), arr, n);
                sorting_by_comp(string(argv[2]), arr, n, comp);
            }
            algoOutput(argv[argc - 1], comp, time);
        }

        else {
            n = atoi(argv[3]);
            arr = new int[n];
            cout << "Input size: " << n << endl;
            if (argc == 6){
                string order, file = "input.txt";
                if (string(argv[4]) == "-rand"){ 
                    order = "Randomize";
                    GenerateRandomData(arr, n);
                }
                else if (string(argv[4]) == "-nsorted") {
                    order = "Nearly Sorted";
                    GenerateNearlySortedData(arr, n);
                }
                else if (string(argv[4]) == "-sorted") {
                    order = "Sorted";
                    GenerateSortedData(arr, n);
                }
                else if (string(argv[4]) == "-rev") {
                    order = "Reversed";
                    GenerateReverseData(arr, n);
                }
                writeFile(file, arr, n);

                if (string(argv[argc - 1]) == "-time")
                    sorting_by_time(string(argv[2]), arr, n, time);
                else if (string(argv[argc - 1]) == "-comp")
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                else {
                    sorting_by_time(string(argv[2]), arr, n, time);
                    readFile(file, arr, n);
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                }

                algoOutput(argv[argc - 1], comp, time, order);
            }
            else if (argc == 5){
                string order = "Randomize";
                GenerateRandomData(arr, n);
                writeFile("input_1.txt", arr, n);
                if (string(argv[argc - 1]) == "-time")
                    sorting_by_time(string(argv[2]), arr, n, time);
                else if (string(argv[argc - 1]) == "-comp")
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                else {
                    sorting_by_time(string(argv[2]), arr, n, time);
                    readFile("input_1.txt", arr, n);
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                }
                algoOutput(argv[argc - 1], comp, time, order);

                order = "Nearly Sorted";
                GenerateNearlySortedData(arr, n);
                writeFile("input_2.txt", arr, n);
                if (string(argv[argc - 1]) == "-time")
                    sorting_by_time(string(argv[2]), arr, n, time);
                else if (string(argv[argc - 1]) == "-comp")
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                else {
                    sorting_by_time(string(argv[2]), arr, n, time);
                    readFile("input_2.txt", arr, n);
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                }
                algoOutput(argv[argc - 1], comp, time, order);

                order = "Sorted";
                GenerateSortedData(arr, n);
                writeFile("input_3.txt", arr, n);
                if (string(argv[argc - 1]) == "-time")
                    sorting_by_time(string(argv[2]), arr, n, time);
                else if (string(argv[argc - 1]) == "-comp")
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                else {
                    sorting_by_time(string(argv[2]), arr, n, time);
                    readFile("input_3.txt", arr, n);
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                }
                algoOutput(argv[argc - 1], comp, time, order);

                order = "Reversed";
                GenerateReverseData(arr, n);
                writeFile("input_4.txt", arr, n);
                if (string(argv[argc - 1]) == "-time")
                    sorting_by_time(string(argv[2]), arr, n, time);
                else if (string(argv[argc - 1]) == "-comp")
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                else {
                    sorting_by_time(string(argv[2]), arr, n, time);
                    readFile("input_4.txt", arr, n);
                    sorting_by_comp(string(argv[2]), arr, n, comp);
                }
                algoOutput(argv[argc - 1], comp, time, order);
            }   
        }
        writeFile("output.txt", arr, n);
        delete[] arr;
    }
    else if(string(argv[1]) == "-c"){
        cout << "COMPARE MODE" << endl;
        cout << "Algorithm: " << argv[2] << " | " << argv[3] << endl;
        
        int n, *arr;
        long long comp1 = 0, comp2 = 0;
        double time1 = 0, time2 = 0;

        if (string(argv[4]).find(".txt") != -1){
            cout << "Input file: " << argv[4] << endl;
            readFile(string(argv[4]), arr, n);
            sorting_by_time(string(argv[2]), arr, n, time1);
            readFile(string(argv[4]), arr, n);
            sorting_by_comp(string(argv[2]), arr, n, comp1);
 
            readFile(string(argv[4]), arr, n);
            sorting_by_time(string(argv[3]), arr, n, time2);
            readFile(string(argv[4]), arr, n);
            sorting_by_comp(string(argv[3]), arr, n, comp2);
            
            cout << "Input size: " << n << endl;
            compOutput(argv[argc - 1], comp1, comp2, time1, time2);
        }
        else {
            n = atoi(argv[4]);
            arr = new int[n];
            cout << "Input size: " << n << endl;
            string order, file = "input.txt";
            if (string(argv[5]) == "-rand"){ 
                order = "Randomize";
                GenerateRandomData(arr, n);
            }
            else if (string(argv[5]) == "-nsorted") {
                order = "Nearly Sorted";
                GenerateNearlySortedData(arr, n);
            }
            else if (string(argv[5]) == "-sorted") {
                order = "Sorted";
                GenerateSortedData(arr, n);
            }
            else if (string(argv[5]) == "-rev") {
                order = "Reversed";
                GenerateReverseData(arr, n);
            }
            writeFile(file, arr, n);
            cout << "Input order: " << order << endl;
            sorting_by_time(string(argv[2]), arr, n, time1);
            readFile(file, arr, n);
            sorting_by_comp(string(argv[2]), arr, n, comp1);
            readFile(file, arr, n);
            sorting_by_time(string(argv[3]), arr, n, time2);
            readFile(file, arr, n);
            sorting_by_comp(string(argv[3]), arr, n, comp2);
            compOutput(argv[argc - 1], comp1, comp2, time1, time2);       
        }
        delete[] arr;
    }

    return 0;
}