
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector()
{
    // TODO Auto-generated constructor stub
    correlation_threshold = 0.9;
}
bool HybridAnomalyDetector::is_anomaly(Point *p, correlatedFeatures c)
{
    if (c.corrlation < correlation_threshold && c.corrlation > 0.5)
    {
        if (!point_in_circle(*p, *(c.circle)))
        {
            return true;
        }
        else
            return false;
    }
    else
        return SimpleAnomalyDetector::is_anomaly(p, c);
}
correlatedFeatures HybridAnomalyDetector::createcorrelatedfeature(Point **p, int size1, correlatedFeatures c)
{
    if (c.corrlation < correlation_threshold && c.corrlation > 0.5)
    {
        Circle minCircle = findMinCircle(p, size1);
        c.circle = new Circle(minCircle.center, minCircle.radius * 1.1);
        return c;
    }
    else
        return SimpleAnomalyDetector::createcorrelatedfeature(p, size1, c);
}

HybridAnomalyDetector::~HybridAnomalyDetector()
{
    // TODO Auto-generated destructor stub
}
