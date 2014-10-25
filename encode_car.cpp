#include <fstream>
#include <iostream>

#include "test/Car.hpp"

using namespace test;

char VEHICLE_CODE[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
char MANUFACTURER_CODE[] = { '1', '2', '3' };
const char *MAKE = "Honda";
const char *MODEL = "Civic VTi";
const int messageHeaderVersion = 0;

void encodeCar( Car &car, char *buffer, int offset, int bufferLength )
{
    car.wrapForEncode( buffer, offset, bufferLength )
       .serialNumber( 1234 )
       .modelYear( 2013 )
       .available( BooleanType::TRUE )
       .code( Model::A )
       .putVehicleCode( VEHICLE_CODE );

    for( int i = 0, size = car.someNumbersLength(); i < size; i++ ) {
        car.someNumbers(i, i);
    }

    car.extras().clear()
       .cruiseControl( true )
       .sportsPack( true )
       .sunRoof( false );

    car.engine()
       .capacity( 2000 )
       .numCylinders( (short)4 )
       .putManufacturerCode( MANUFACTURER_CODE );

    car.fuelFiguresCount( 3 )
       .next().speed( 30 ).mpg( 35.9f )
       .next().speed( 55 ).mpg( 49.0f )
       .next().speed( 75 ).mpg( 40.0f );

    Car::PerformanceFigures &performanceFigures = car.performanceFiguresCount( 2 );

    performanceFigures.next()
        .octaneRating( (short)95 )
        .accelerationCount( 3 )
            .next().mph( 30 ).seconds( 4.0f )
            .next().mph( 60 ).seconds( 7.5f )
            .next().mph( 100 ).seconds( 12.2f );

    performanceFigures.next()
        .octaneRating( (short)99 )
        .accelerationCount( 3 )
            .next().mph( 30 ).seconds( 3.8f )
            .next().mph( 60 ).seconds( 7.1f )
            .next().mph( 100 ).seconds( 11.8f );
}

int main( int argc, const char* argv[] )
{
    char buffer[2048];

    // encode car to buffer
    Car car;
    encodeCar( car, buffer, 0, sizeof(buffer) );

    // write encoded buffer to disk
    std::ofstream file( "car.bin", std::ofstream::binary | std::ofstream::trunc );
    file.write( car.buffer(), car.size() );
    file.close();
}
