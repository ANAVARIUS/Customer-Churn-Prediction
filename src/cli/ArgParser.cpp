#include "../../include/cli/ArgParser.hpp"

ArgParser::ArgParser(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
        args.push_back(argv[i]);
};

void ArgParser::run()
{
    auto now = std::chrono::system_clock::now();
    std::string datetime = std::format("{:%Y-%m-%d-%H-%M-%S}", now);
    Logger::instance().set_file("logs/CSP_" + datetime);

    bool skipped_first_argument = false;
    for (auto& arg : args) {
        if(!skipped_first_argument)
        {
            skipped_first_argument = true;
            continue;
        }
        if(arg=="--help")
        {
            showHelp();
            return;
        }
        if(arg=="--train")
        {
            //Train a model and save it
            if(arg=="--evaluate")
            {
                Logger::instance().log("Customer Churn Predictor running in training mode with evaluation metrics.");
                handleEvaluate();
                return;
            }
            Logger::instance().log("Customer Churn Predictor running in training mode.");
            void handleTrain();
            return;
        }
        if(arg=="--predict")
        {
            Logger::instance().log("Customer Churn Predictor running in predict mode.");
            //Load a model and predict multiple inputs
            void handlePredict();
            return;
        }
        if(arg=="--predict-single")
        {
            Logger::instance().log("Customer Churn Predictor running in single predict mode.");
            //Load a model and make a single prediction
            void handleSinglePredict();
            return;
        }
        throw std::runtime_error("Unknown option: " + arg);
    }
};

void ArgParser::showHelp() const
{
    std::cout << "Customer Churn Predictor - Command Line Interface\n"
              << "--------------------------------------------------\n"
              << "Usage:\n"
              << "  ./logistic_churn [OPTION]\n\n"
              << "Options:\n"
              << "  --help             Show this help message and exit\n"
              << "  --train            Train a new model\n"
              << "  --train --evaluate Train a model and evaluate its accuracy\n"
              << "  --predict          Predict churn using an existing trained model\n"
              << "Examples:\n"
              << "  ./logistic_churn --train\n"
              << "  ./logistic_churn --train --evaluate\n"
              << "  ./logistic_churn --predict\n"
              << "Log files are saved under the 'logs/' directory with timestamped names.\n";
};

void ArgParser::handleTrain()
{
    std::string filePath, destinationPath;
    bool hasHeader;
    size_t churnColumn;
    std::vector<size_t> dropColumns;
    double alpha;
    int epochs;
    collectTrainData(std::string& filePath,
                     std::string& destinationPath,
                     bool hasHeader,
                     size_t churnColumn,
                     std::vector<size_t> dropColumns,
                     double alpha,
                     int epochs);

    Logger::instance.log("Trying to parse CSV...");
    std::vector<std::vector<std::string>> csv = CSVReader::readCSV(FilePath);
    ProcessedData data = CSVReader::preprocess(csv, header, churnColumn, dropColumns);
    std::unique_ptr<Splitter> splitter = std::make_unique<RandomSplitter>();
    auto [train, test] splits = splitter->split(data, 0.8);
    Logger::instance.log("Sucess");
    Logger::instance.log("Initializing model...");
    LogisticRegression model(data.features.size());
    model.train(train, alpha, epochs);
    model.save(destinationPath);
    Logger::instance.log("Sucess");
    Logger::instance.log("Program finished succesfully.");
};

void ArgParser::handlePredict()
{
    std::string filePath, destinationPath, weightsPath;
    bool hasHeader;
    std::vector<size_t> dropColumns;
    collectPredictData( filePath,
                        destinationPath,
                        weightsPath,
                        hasHeader,
                        sdropColumns);
    Logger::instance.log("Trying to parse CSV...");
    std::vector<std::vector<std::string>> csv = CSVReader::readCSV(FilePath);
    ProcessedData data = CSVReader::preprocess(csv, header, churnColumn, dropColumns);
    Logger::instance.log("Sucess");
    Logger::instance.log("Initializing model...");
    LogisticRegression model(data.features.size());
    model.load(weightsPath);
    std::vector<double> predictions;
    for(auto& row: data.features)
    {
        double prediction = model.predict(row);
        predictions.push_back(prediction);
    }
    saveToCSVFile(predictions, destinationPath);
    Logger::instance.log("Sucess");
    Logger::instance.log("Program finished succesfully.");
};

void ArgParser::handleEvaluate()
{
    std::string filePath, destinationPath;
    bool hasHeader;
    size_t churnColumn;
    std::vector<size_t> dropColumns;
    double alpha, accuracy_v, precision_v, recall_v, f1Score_v;
    int epochs;
    collectTrainData(std::string& filePath,
                     std::string& destinationPath,
                     bool hasHeader,
                     size_t churnColumn,
                     std::vector<size_t> dropColumns,
                     double alpha,
                     int epochs);

    Logger::instance.log("Trying to parse CSV...");
    std::vector<std::vector<std::string>> csv = CSVReader::readCSV(FilePath);
    ProcessedData data = CSVReader::preprocess(csv, header, churnColumn, dropColumns);
    std::unique_ptr<Splitter> splitter = std::make_unique<RandomSplitter>();
    auto [train, test] splits = splitter->split(data, 0.8);
    Logger::instance.log("Sucess");
    Logger::instance.log("Initializing model...");
    LogisticRegression model(data.features.size());
    model.train(train, alpha, epochs);
    model.save(destinationPath);
    Logger::instance.log("Sucess");
    Logger::instance.log("Obtaining metrics..."
    accuracy_v = model.accuracy(test);
    precision_v = model.precision(test);
    recall_v = model.recall(test);
    f1score_v = model.f1score(test);
    std::cout << "Accuracy: " << accuracy_v << std::endl;
    std::cout << "Precision: " << precision_v << std::endl;
    std::cout << "Recall: " << recall_v << std::endl;
    std::cout << "F1 score: " << f1score_v << std::endl;
    std::string metrics =
    "Accuracy: " + std::string(accuracy_v) + "\n"+
    "Precision: " + std::string(precision_v) + "\n"+
    "Recall: " + std::string(recall_v) + "\n"+
    "F1 score: " + std::string(f1score_v);
    Logger::instance.log(metrics);
    Logger::instance.log("Program finished succesfully.");
};

void ArgParser::collectTrainData(  std::string& filePath,
                        std::string& destinationPath,
                        bool& hasHeader,
                        size_t& churnColumn,
                        std::vector<size_t>& dropColumns,
                        double& alpha,
                        int& epochs)
{
    std::string header;
    size_t dropColumn;
    std::cout<<"Enter the dataset file location:\n";
    std::cin>>filePath;
    std::cout<<"Enter the destination output file location:\n";
    std::cin>>destinationPath;
    std::cout<<"Does it have a header? (y/n): ";
    std::cin>> header;
    if(hasHeader == "y")
        hasHeader = true;
    else if(hasHeader == "n")
        hasHeader = false;
    else throw std::runtime_error("Invalid response: " + header);
    std::cout<<"Enter the index of the column that contains the results (weather the client churned or not):\n"
    <<"(0 indexed)\n";
    std::cin>> churnColumn;
    std::cout<<
    "Enter the indices of the columns you want to drop (press enter if you don't want any columns to be dropped):\n"
    <<"(These can be IDs or data with weak or nonexistent correlation to the churn. Enter the numbers space-separated)\n";
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    int index;
    while (iss >> index) {
        dropColumns.push_back(index);
    }

    std::cout<<"Enter the learning rate\n";
    std::cin>>alpha;
    std::cout<<"Enter the number of epochs\n";
    std::cin>> epochs;
};

void ArgParser::collectPredictData(  std::string& filePath,
                        std::string& destinationPath,
                        std::string& weightsPath,
                        bool& hasHeader,
                        std::vector<size_t>& dropColumns)
{
    std::string header;
    size_t dropColumn;
    std::cout<<"Enter the weights file location:\n";
    std::cin>>weightsPath;
    std::cout<<"Enter the dataset file location:\n";
    std::cin>>filePath;
    std::cout<<"Enter the destination output file location:\n";
    std::cin>>destinationPath;
    std::cout<<"Does it have a header? (y/n): ";
    std::cin>> header;
    if(hasHeader == "y")
        hasHeader = true;
    else if(hasHeader == "n")
        hasHeader = false;
    else throw std::runtime_error("Invalid response: " + header);
    std::cout<<
    "Enter the indices of the columns you want to drop (press enter if you don't want any columns to be dropped):\n"
    <<"(These can be IDs or data with weak or nonexistent correlation to the churn. Enter the numbers space-separated)\n";
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    int index;
    while (iss >> index) {
        dropColumns.push_back(index);
    }
};

void ArgParser::saveToCSVFile(std::vector<double>& predictions, std::string destinationPath)
{
    std::ofstream outputFile(destinationPath, std::ios::out);

    if (!outputFile.is_open()) {
        Logger::instance.log("Error opening file!" );
        throw runtime_error("Error opening file!");
        return 1;
    }
    for (const auto& row : predictions) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << row[i];
            if (i < row.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << std::endl;
    }
    outputFile.close();
};