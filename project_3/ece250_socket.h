// Used in CLASSIFY command to work with the language model classifier
// Formats input data into JSON, uses HTTP POST to send data to server, parse server's response to get classification

#ifndef MY_SOCKET_H
#define MY_SOCKET_H

#include <string>

// Function to send a POST request and return the response as a string
    // host: hostname of server
    // path: URL path for POST request
    // data: JSON data (payload) to send
    // port: port to connect to
std::string sendPostRequest(const std::string& host, const std::string& path, const std::string& data, int port);   

// Function to extract the first label from a JSON response (parse response and extract first result for classification)
std::string extractFirstLabel(const std::string& response);   // response: raw JSON response from server

// Function to classify text and return the first label
    // textToClassify: input text to classify
    // candidateLabels: possible labels of classification
std::string labelText(const std::string& textToClassify, const std::string& candidateLabels);

#endif // MY_SOCKET_H
