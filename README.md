sbe_tests
=========

Simple test programs demonstrating encoding with c++ and decoding with python

# generate cpp and python code
java -Dsbe.target.language=Python -jar ../simple-binary-encoding/target/dist/sbe.jar car.xml
java -Dsbe.target.language=Cpp98 -jar ../simple-binary-encoding/target/dist/sbe.jar car.xml
echo "" > test/__init__.py

# encode car using cpp
g++ -I. -I../simple-binary-encoding/main/cpp encode_car.cpp
./a.out

# decode car using python
python decode_car.py
