#include "CLI.h"
#include "iostream"
#include "vector"
#include "AnomalyDetector.h"
CLI::CLI(DefaultIO *dio)
{
    this->dio = dio;
    this->data = new Data();
    this->data->detector = HybridAnomalyDetector();
    this->uploadCommand = new Upload_command(dio, data);
    this->algorithemSettingCommand = new Algorithem_setting_command(dio, data);
    this->anomalyDetectionCommand = new Anomaly_detection_command(dio, data);
    this->displayResultsCommand = new Display_results_command(dio, data);
    this->analyzeResultsCommand = new Analyze_results_command(dio, data);
    this->exitCommand = new Exit_command(dio, data);

    cammands.push_back(uploadCommand);
    cammands.push_back(algorithemSettingCommand);
    cammands.push_back(anomalyDetectionCommand);
    cammands.push_back(displayResultsCommand);
    cammands.push_back(analyzeResultsCommand);
    cammands.push_back(exitCommand);
}

void CLI::start()
{
    string menu_choice_str;
    int menu_choice = 0;
    while (menu_choice != 5)
    {
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        //cout<<cammands[0]->description;
        for (int i = 0; i < cammands.size(); i++)
        {
            dio->write(cammands[i]->description);
            //cout<<cammands[i]->description;
        }
        menu_choice_str = dio->read();

        menu_choice = atoi(menu_choice_str.c_str()) - 1;

        cammands.at(menu_choice)->execute();
    }
}

CLI::~CLI()
{
    delete uploadCommand;
    delete analyzeResultsCommand;
    delete anomalyDetectionCommand;
    delete displayResultsCommand;
    delete algorithemSettingCommand;
    delete data;
}
