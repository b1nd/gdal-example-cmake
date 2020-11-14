#include <iostream>

#include "gdal.h"
#include "ogrsf_frmts.h"

using namespace std;

void printPolygonInfo(OGRPolygon* polygon) {
    auto* exteriorRing = polygon->getExteriorRing();
    cout << "Number of points in Poligon: " << exteriorRing->getNumPoints() << endl;
    cout << "First 10 points: ";
    int count = 10;
    for (auto&& point : exteriorRing) {
        if (count-- <= 0) break;
        cout << "Point(" << point.getX() << "," << point.getY() << "); ";
    }
    cout << endl;
}

int main() {
    GDALAllRegister();

    GDALDataset* dataset = static_cast<GDALDataset*>(GDALOpenEx(
        R"(.\..\mow-data\boundary-polygon.shp)",
        GDAL_OF_VECTOR,
        nullptr, nullptr, nullptr));

    if (dataset == nullptr) {
        cout << "Cannot open file!" << endl;
        return -1;
    }

    for (auto&& layer : dataset->GetLayers()) {
        for (auto&& feature : layer) {
            auto* geometry = feature->GetGeometryRef();

            switch (auto geometryType = geometry->getGeometryType()) {

            case wkbPolygon: {
                cout << "This is Polygon!" << endl;
                printPolygonInfo(geometry->toPolygon());
                break;
            }
            case wkbMultiPolygon: {
                cout << "This is MultiPolygon!" << endl;
                auto* multiPoligon = geometry->toMultiPolygon();

                int i = 1;
                for (auto&& poligon : multiPoligon) {
                    cout << "Polygon #" << i++ << ":" << endl;
                    printPolygonInfo(poligon);
                }
                break;
            }
            default:
                cout << "Skip geometry with type: " << geometryType << endl;
            }
            cout << endl;
        }
    }

    return 0;
}
