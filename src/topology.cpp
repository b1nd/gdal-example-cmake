#include <iostream>

#include "ogrsf_frmts.h"
#include "gdal.h"

using namespace std;

int main() {
    GDALAllRegister();

    shared_ptr<OGRPolygon> polygon1(new OGRPolygon());

    shared_ptr<OGRLinearRing> ring(new OGRLinearRing());
    ring->addPoint(50, 50);
    const shared_ptr<OGRPoint> point(new OGRPoint(100, 50));
    ring->addPoint(point.get());
    ring->addPoint(100, 0);
    ring->addPoint(0, 0);
    ring->addPoint(0, 50);
    ring->addPoint(50, 50); // ring closing point, same as first point

    polygon1->addRing(ring.get());

    const shared_ptr<OGRPolygon> polygon2(new OGRPolygon());
    char polygon2WKT[] = "POLYGON ((25 25, 150 50, 100 -25, 10 -10, 25 25))";
    const shared_ptr<char*> wktStringArray(new char*[1]{polygon2WKT});
    OGR_G_ImportFromWkt(polygon2.get(), wktStringArray.get());

    cout << "polygon1 area: " << polygon1->get_Area() << endl;
    cout << "polygon2 area: " << polygon2->get_Area() << "\n" << endl;

    cout << "polygon1 intersects polygon2: " << polygon1->Intersects(polygon2.get()) << endl;
    cout << "polygon1 touches polygon2: " << polygon1->Touches(polygon2.get()) << endl;
    cout << "polygon1 contains polygon2: " << polygon1->Contains(polygon2.get()) << endl;

    const shared_ptr<OGREnvelope> polygon1Envelope(new OGREnvelope);
    polygon1->getEnvelope(polygon1Envelope.get());
    cout << "\n" << "polygon1 envelope:\n" <<
        "min x: " << polygon1Envelope->MinX << "\n" <<
        "max x: " << polygon1Envelope->MaxX << "\n" <<
        "min y: " << polygon1Envelope->MinY << "\n" <<
        "max y: " << polygon1Envelope->MaxY << endl;

    return 0;
}
