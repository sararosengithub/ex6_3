

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "timeseries.h"
#include "minCircle.h"
//float CORRLATION = 0.9;
struct correlatedFeatures
{
    string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle *circle = nullptr;
    correlatedFeatures(string f1, string f2, float cor)
    {
        feature1 = f1;
        feature2 = f2;
        corrlation = cor;
    }
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector
{
protected:
    vector<correlatedFeatures> cf;
    float correlation_threshold;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);
    virtual vector<AnomalyReport> detect(const TimeSeries &ts);
    virtual bool is_anomaly(Point *p, correlatedFeatures c);
    virtual vector<correlatedFeatures> getNormalModel()
    {
        return cf;
    }

    virtual correlatedFeatures createcorrelatedfeature(Point **p, int size1, correlatedFeatures c);
    //virtual float get_correlation_threshold();
    //virtual void set_correlation_threshold(float f);
    virtual float get_correlation_threshold() { return correlation_threshold; }
    virtual void set_correlation_threshold(float f)
    {
        correlation_threshold = f;
    }
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
