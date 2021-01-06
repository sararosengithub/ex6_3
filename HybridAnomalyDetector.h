

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    //void calculate_linear_regression(const TimeSeries &ts);
    virtual bool is_anomaly(Point *p,correlatedFeatures c);
    virtual correlatedFeatures createcorrelatedfeature(Point **p, int size1, correlatedFeatures c);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
