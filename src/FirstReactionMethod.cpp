#include "../include/FirstReactionMethod.hpp"

void FirstReactionMethod::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    model->loadModel(filename);
    this->simulTime = simulTime;
    methodOutName = "FRM_output";
    if (model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
        t = new double[model->getReacNumber()];
    }
}
void FirstReactionMethod::perform(string filename, double simulTime)
{
    cout << "FIRST REACTION METHOD" << endl;
    initialization(filename, simulTime);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = 0.0;
    int *xArray;
    x.clear();
    calcPropensity();
    while (currentTime <= simulTime)
    {
        xArray = new int[model->getSpecNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            xArray[i] = specQuantity[i];
        }
        x.insert(make_pair(currentTime, xArray));
        //generate simulation time
        reacTimeGeneration();
        //reaction selection
        reacSelection();
        //reaction execution
        reacExecution();
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    printResult();
    saveToFile();
}
void FirstReactionMethod::reacExecution()
{
    //updates the species quantities of the selected reaction
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[selectedReaction][i];
    }
}
void FirstReactionMethod::reacTimeGeneration()
{
    //generates the absolute time
    double u = 0.0;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        u = ut->getRandomNumber();
        t[i] = (-1.0) * ut->ln(u) / propArray[i];
    }
}
void FirstReactionMethod::reacSelection()
{
    //selects the minimal time and updates the current time
    double minT = t[0];
    selectedReaction = 0;
    for (int i = 1; i < model->getReacNumber(); i++)
    {
        if (minT > t[i])
        {
            minT = t[i];
            selectedReaction = i;
        }
    }
    currentTime = currentTime + minT;
}
void FirstReactionMethod::calcPropensity()
{
    int sum = 1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        sum = 1;
        for (int j = 0; j < model->getSpecNumber(); j++)
        {
            sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[i][j]);
        }
        propArray[i] = model->getReacRateArray()[i] * sum;
    }
}
void FirstReactionMethod::calcPropOne(int index)
{
    int sum = 1;
    for (int j = 0; j < model->getSpecNumber(); j++)
    {
        sum *= ut->binomialCoefficient(specQuantity[j], model->getReactants()[index][j]);
    }
    propArray[index] = model->getReacRateArray()[index] * sum;
}
FirstReactionMethod::~FirstReactionMethod()
{
    //dtor
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] t;
}