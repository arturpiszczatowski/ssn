#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

using weight = vector<double>;
using neuron = vector<vector<double>>;
using network = vector<vector<vector<double>>>;

neuron neuron_maker(double input, vector<double> weights){
    neuron new_neuron = {{input},
                         {weights}};
    return new_neuron;
}

void generate_graphviz(vector<double> graph_inputs, vector<double> graph_biases, vector<double> graph_weights, double output){

    string graph_code = "digraph G {\n"
                        "\"input_1= " + to_string(graph_inputs[0]) + "\"" + " -> \"n1{bias=" + to_string(graph_biases[0]) + "}\" [taillabel = \"weight=" + to_string(graph_weights[0]) + "\"]\n" +
                        "\"input_2= " + to_string(graph_inputs[1]) + "\"" + " -> \"n2{bias=" + to_string(graph_biases[1]) + "}\" [taillabel = \"weight=" + to_string(graph_weights[1]) + "\"]\n" +
                        "\"n2{bias=" + to_string(graph_biases[1]) + "}\"" + " -> \"n3{bias=" + to_string(graph_biases[2]) + "}\"" + " [taillabel = \"weight=" + to_string(graph_weights[2]) + "\"]\n" +
                        "\"n1{bias=" + to_string(graph_biases[0]) + "}\"" + " -> \"n3{bias=" + to_string(graph_biases[2]) + "}\"" + " [taillabel = \"weight=" + to_string(graph_weights[3]) + "\"]\n" +
                        "\"n3{bias=" + to_string(graph_biases[2]) + "}\"" + " -> " + to_string(output) + "\n}";

    ofstream out("output.txt");
    out << setprecision(2) << graph_code;
    out.close();
}

void show_network(vector<double> graph_inputs, vector<double> graph_biases, vector<double> graph_weights, double output){

}

int xor_function(network current_network){

    neuron neuron_1 = current_network[0];
    neuron neuron_2 = current_network[1];


    double input_1 = neuron_1[0][0];
    double input_2 = neuron_2[0][0];

    weight weight_1;
    weight_1.push_back(neuron_1[1][0]);
    weight_1.push_back(neuron_1[1][1]);
    weight_1.push_back(neuron_1[1][2]);

    double bias_1 = weight_1[0];

    weight weight_2;
    weight_2.push_back(neuron_2[1][0]);
    weight_2.push_back(neuron_2[1][1]);
    weight_2.push_back(neuron_2[1][2]);

    double bias_2 = weight_2[0];

    double induction_1 = bias_1 + input_1 * weight_1[1] + input_2 * weight_1[2];
    double induction_2 = bias_2 + input_1 * weight_2[1] + input_2 * weight_2[2];


    double activation_1 = induction_1 < 0 ? 0:1;
    double activation_2 = induction_2 < 0 ? 0:1;

    neuron neuron_3=current_network[2];

    input_1 = activation_1;
    input_2 = activation_2;

    weight weight_3;
    weight_3.push_back(neuron_3[1][0]);
    weight_3.push_back(neuron_3[1][1]);
    weight_3.push_back(neuron_3[1][2]);

    double bias_3 = weight_3[0];

    double induction_3 = bias_3 + input_1 * weight_3[1] + input_2 * weight_3[2];

    double activation_3 = induction_3 < 0 ? 0:1;

    return activation_3;
}


// Homework network
//      -- N1 --
//              \
//               N3 --
//              /
//      -- N2 --

double simple_network_function(network current_network){

    neuron neuron_1 = current_network[0];
    neuron neuron_2 = current_network[1];


    double input_1 = neuron_1[0][0];
    double input_2 = neuron_2[0][0];

    weight weight_1;
    weight_1.push_back(neuron_1[1][0]);
    weight_1.push_back(neuron_1[1][1]);

    double bias_1 = weight_1[0];

    weight weight_2;
    weight_2.push_back(neuron_2[1][0]);
    weight_2.push_back(neuron_2[1][1]);

    double bias_2 = weight_2[0];

    double induction_1 = bias_1 + input_1 * weight_1[1];
    double induction_2 = bias_2 + input_2 * weight_2[1];


    double activation_1 = induction_1 < 0 ? 0:1;
    double activation_2 = induction_2 < 0 ? 0:1;

    neuron neuron_3=current_network[2];

    input_1 = activation_1;
    input_2 = activation_2;

    weight weight_3;
    weight_3.push_back(neuron_3[1][0]);
    weight_3.push_back(neuron_3[1][1]);
    weight_3.push_back(neuron_3[1][2]);

    double bias_3 = weight_3[0];

    double induction_3 = bias_3 + input_1 * weight_3[1] + input_2 * weight_3[2];

    double activation_3 = induction_3 < 0 ? 0:1;

    vector<double> graph_inputs{neuron_1[0][0], neuron_2[0][0]};
    vector<double> graph_biases{bias_1, bias_2, bias_3};
    vector<double> graph_weights{weight_1[1], weight_2[1], weight_3[1], weight_3[2]};

    generate_graphviz(graph_inputs, graph_biases, graph_weights, activation_3);

    return activation_3;
}

int main(int argc, char** argv)
{
    double input_1 = stof(argv[1]);
    double input_2 = stof(argv[2]);


    vector<double> weights_1 = {-0.5, 1};
    vector<double> weights_2 = {1.5, -1};
    vector<double> weights_3 = {-1.5, 1, 1};

    //xor neurons
    neuron neuron_1 = neuron_maker(input_1, weights_1);
    neuron neuron_2 = neuron_maker(input_2, weights_2);
    neuron neuron_3 = neuron_maker({},weights_3);

    //xor network
    network new_network = {neuron_1,
                           neuron_2,
                           neuron_3};

    cout << simple_network_function(new_network);

}


