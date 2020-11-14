#include "ogrsf_frmts.h"
#include <iostream>
#include <fstream>
#include "gdal.h"

using namespace std;

static const int maxFeatures = 1000;

// see out.txt file
int main() {
    GDALAllRegister();

    GDALDataset* dataset = static_cast<GDALDataset*>(GDALOpenEx(
        R"(.\..\mow-data\building-polygon.shp)",
        GDAL_OF_VECTOR,
        nullptr, nullptr, nullptr));

    if (dataset == nullptr) {
        cout << "Cannot open file!" << endl;
        return -1;
    }

    ofstream out;
    out.open("out.txt");

    for (auto&& layer : dataset->GetLayers()) {
        out << "Layer total features: " << layer->GetFeatureCount() << endl;

        int i = 1;
        for (auto&& feature : layer) {
            if (i > maxFeatures) break;
            out << "Feature #" << i++ << " field count: " << feature->GetFieldCount() << endl;

            for (auto&& field : feature) {
                out << field.GetName() << ":";
                switch (field.GetType()) {
                case OFTReal:
                    out << field.GetDouble();
                    break;
                case OFTString:
                    // cout << field.GetString(); // error
                    out << field.GetAsString();
                    break;
                default:
                    out << field.GetAsString();
                    break;
                }
                out << "; ";
            }
            out << endl;
        }
    }
    return 0;
}
