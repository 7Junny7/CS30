//
// Created by Jun Kim on 3/11/22.
//
#include "Map.h"
#include <iostream>
#include <cassert>
#include <type_traits>
using namespace std;

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
              "Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
              "Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
    CHECKTYPE(&Map::empty,          bool (Map::*)() const);
    CHECKTYPE(&Map::size,           int  (Map::*)() const);
    CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
    CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
    CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
    CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
    CHECKTYPE(&Map::swap,           void (Map::*)(Map&));

    CHECKTYPE(combine,  bool (*)(const Map&, const Map&, Map&));
    CHECKTYPE(subtract, void (*)(const Map&, const Map&, Map&));
}

//void test()
//{
//    Map m;
//    assert(m.insert(123, "Fred"));
//    assert(m.insert(456, "Ethel"));
//    assert(m.size() == 2);
//    string s;
//    assert(m.get(123, s)  &&  s == "Fred");
//    s = "";
//    int i1;
//    assert(m.get(0, i1, s)  &&
//           ((i1 == 123  &&  s == "Fred")  ||  (i1 == 456  &&  s == "Ethel")));
//    int i2;
//    assert(m.get(1, i2, s)  &&  i1 != i2  &&
//           ((i2 == 123  &&  s == "Fred")  ||  (i2 == 456  &&  s == "Ethel")));
//}

void test()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    double d = 42;
    assert(m.get("Fred", d)  &&  d == 123);
    d = 42;
    string s1;
    assert(m.get(0, s1, d)  &&
           ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
    string s2;
    assert(m.get(1, s2, d)  &&  s1 != s2  &&
           ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
}
int main() {
    try{
        //#1 - checking insert, size, and get(n,k,v) functions
        //default constructor
        Map m;
        //insert hash
        m.insert("A", 10);
        m.insert("B", 44);
        m.insert("C", 10);
        string all;
        double total = 0;
        for (int n = 0; n < m.size(); n++)
        {
            string k;
            double v;
            //get hash
            m.get(n, k, v);
            all += k;
            total += v;
        }
        //print result value
        cout << all << total <<endl;
        cout << "Test case 1 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 1"<<endl;
    }

    try{
        //#2 - checking insert, and get(n,k,v) functions
        //default constructor
        Map gpas;
        //insert hash
        gpas.insert("Fred", 2.956);
        gpas.insert("Ethel", 3.538);
        double v;
        string k1;
        //get hash and test
        assert(gpas.get(1,k1,v)  &&  (k1 == "Fred"  ||  k1 == "Ethel"));
        string k2;
        assert(gpas.get(1,k2,v)  &&  k2 == k1);
        cout << "Test case 2 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 2"<<endl;
    }

    try{
        //#3 - checking insert, contains, erase, and size functions
        //default constructor
        Map gpas;
        //insert hash
        gpas.insert("Fred", 2.956);
        //test contains function if the key doesn't exist
        assert(!gpas.contains(""));
        gpas.insert("Ethel", 3.538);
        gpas.insert("", 4.000);
        gpas.insert("Lucy", 2.956);
        //test contains function if the key exists
        assert(gpas.contains(""));
        //erase hash
        gpas.erase("Fred");
        //test the result of erase function
        assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
               gpas.contains(""));
        cout << "Test case 3 passed"<<endl;
    }catch (...){
        cerr<<"Test failed at case 3"<<endl;
    }

    try{
        //#4 - checking insert, swap, size, and contains functions
        //default constructor
        Map m1;
        //insert hash
        m1.insert("Fred", 2.956);
        Map m2;
        m2.insert("Ethel", 3.538);
        m2.insert("Lucy", 2.956);
        //swap m1 and m2
        m1.swap(m2);
        //test the result of swap function
        assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
               m2.size() == 1  &&  m2.contains("Fred"));
        cout << "Test case 4 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 4"<<endl;
    }

    try{
        //#5 - checking update, and get functions
        //default constructor
        Map gpas;
        //insert hash over the size of the hash table
        gpas.insert("A", 1.11);
        gpas.insert("B", 2.22);
        gpas.insert("C", 3.33);
        gpas.insert("D", 4.44);
        gpas.insert("E", 5.55);
        gpas.insert("F", 6.66);
        gpas.insert("G", 7.77);
        gpas.insert("H", 8.88);
        gpas.insert("I", 9.99);
        gpas.insert("J", 10.00);
        gpas.insert("K", 11.11);
        gpas.insert("a", 12.12);
        gpas.insert("b", 13.13);
        //if the same key already exists
        gpas.insert("A",15.15);
        double v = 3.14;
        //update hash
        gpas.update("A", 99.99);
        //test inserting hash to the hash table through linked list
        //if the key already exists, doesn't insert it
        //if the key exists, update it with the argument value.
        assert(gpas.get("A",v) && v == 99.99);
        cout << "Test case 5 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 5"<<endl;
    }

    try{
        //#6 - checking insertOrUpdate, and get functions
        //dafault constructor
        Map gpas;
        //insert hash
        gpas.insert("A", 1.11);
        gpas.insert("B", 2.22);
        gpas.insert("C", 3.33);
        gpas.insert("D", 4.44);
        gpas.insert("E", 5.55);
        gpas.insert("F", 6.66);
        gpas.insert("G", 7.77);
        gpas.insert("H", 8.88);
        gpas.insert("I", 9.99);
        gpas.insert("J", 10.00);
        gpas.insert("K", 11.11);
        gpas.insert("a", 12.12);
        gpas.insert("b", 13.13);
        gpas.insert("A",15.15);
        double v = 3.123;
        //update hash if it already exists
        gpas.insertOrUpdate("A", 77.77);
        //test the result after update function
        assert(gpas.get("A",v) && v == 77.77);
        //insert hash if it doesn't exist
        gpas.insertOrUpdate("c", 14.14);
        //test the result after insert function
        assert(gpas.get("c",v) && v == 14.14);
        cout << "Test case 6 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 6"<<endl;
    }

    try{
        //#7 - checking Copy constructor function
        //default constructor
        Map gpas;
        //insert hash
        gpas.insert("A", 1.11);
        gpas.insert("B", 2.22);
        gpas.insert("C", 3.33);
        gpas.insert("D", 4.44);
        gpas.insert("E", 5.55);
        gpas.insert("F", 6.66);
        gpas.insert("G", 7.77);
        gpas.insert("H", 8.88);
        gpas.insert("I", 9.99);
        gpas.insert("J", 10.00);
        gpas.insert("K", 11.11);
        gpas.insert("a", 12.12);
        gpas.insert("b", 13.13);
        gpas.insert("A",15.15);
        //copy constructor
        Map gpas2(gpas);
        string k1, k2;
        double v1, v2;
        //test the result of the copy constructor
        assert(gpas2.size() == gpas.size() && gpas2.get(1, k1, v1) &&
               gpas.get(1, k2, v2) && k1 == k2 && v1 == v2);
        cout << "Test case 7 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 7"<<endl;
    }

    try{
        //#8 - checking Assignment operator function
        //default constructor
        Map gpas;
        //insert hash
        gpas.insert("A", 1.11);
        gpas.insert("B", 2.22);
        gpas.insert("C", 3.33);
        gpas.insert("D", 4.44);
        gpas.insert("E", 5.55);
        gpas.insert("F", 6.66);
        gpas.insert("G", 7.77);
        gpas.insert("H", 8.88);
        gpas.insert("I", 9.99);
        gpas.insert("J", 10.00);
        gpas.insert("K", 11.11);
        gpas.insert("a", 12.12);
        gpas.insert("b", 13.13);
        gpas.insert("A",15.15);
        Map gpas2;
        //use assignment operator if lhs is empty
        gpas2 = gpas;
        string k1, k2;
        double v1, v2;
        //test the result of assignment operator when lhs is empty
        assert(gpas2.size() == gpas.size() && gpas2.get(1, k1, v1) &&
               gpas.get(1, k2, v2) && k1 == k2 && v1 == v2);
        Map gpas3;
        gpas3.insert("A",12.35);
        //use assignment operator if lhs is not empty
        gpas3 = gpas;
        //test the result of assignment operator when lhs is not empty
        assert(gpas3.size() == gpas.size() && gpas3.get(1, k1, v1) &&
               gpas.get(1, k2, v2) && k1 == k2 && v1 == v2);
        Map gpas4;
        //use assignment operator if rhs is empty
        gpas3 = gpas4;
        k1 = ""; k2 = "";
        v1 = 0; v2 = 0;
        //test the result of assignment operator when rhs is empty
        assert(gpas3.size() == gpas4.size() && !gpas3.get(0,k1,v1) &&
               !gpas4.get(0,k2,v2) && k1 == k2 && v1 == v2);
        cout << "Test case 8 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 8"<<endl;
    }

    try{
        //#9 - checking Combine function
        //default constructor
        Map gpas;
        //insert hash
        gpas.insert("A", 1.11);
        gpas.insert("B", 2.22);
        gpas.insert("C", 3.33);
        gpas.insert("D", 4.44);
        gpas.insert("E", 5.55);
        gpas.insert("F", 6.66);
        gpas.insert("G", 7.77);
        gpas.insert("H", 8.88);
        gpas.insert("I", 9.99);
        gpas.insert("J", 10.00);
        gpas.insert("K", 11.11);
        gpas.insert("a", 12.12);
        gpas.insert("b", 13.13);
        gpas.insert("A",15.15);
        Map gpas2;
        Map gpas3;
        gpas2.insert("e", 66.66);
        gpas2.insert("f", 67.67);
        gpas2.insert("A", 123.123);
        //test combine function when m1 and m2 is not equal and exists the same key
        assert(!combine(gpas, gpas2, gpas3) && gpas3.size() == 14 &&
               !gpas3.contains("A"));
        Map gpas4;
        gpas4.insert("A",123.123);
        gpas4.insert("B", 133.133);
        gpas4.insert("C", 144.144);
        //test combine function when m2 and result is equal
        assert(combine(gpas2, gpas4, gpas4) && gpas4.size() == 5 &&
               gpas4.contains("A"));
        cout << "Test case 9 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 9"<<endl;
    }

    try{
        //#10 - checking subtract function
        //default constructor
        Map gpas2;
        //insert hash
        gpas2.insert("Fred", 123);
        gpas2.insert("Ethel", 456);
        gpas2.insert("Lucy", 789);
        Map gpas3;
        gpas3.insert("Lucy", 789);
        gpas3.insert("Ricky", 321);
        gpas3.insert("Ethel", 654);
        Map gpas4;
        //use subtract function if m1 and m2 is not equal and exist the same key
        subtract(gpas2, gpas3, gpas4);
        //test the result of subtract function
        assert(gpas4.size() == 1 && gpas4.contains("Fred"));
        //use subtract function if m2 and result is equal
        subtract(gpas2, gpas3, gpas3);
        //test the result of subtract function
        assert(gpas3.size() == 1 && gpas3.contains("Fred"));
        cout << "Test case 10 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 10"<<endl;
    }

    try{
        //#11 :OK
        // default constructor
        Map m;
        // For an empty map:
        assert(m.size() == 0);      // test size
        assert(m.empty());          // test empty
        assert(!m.erase("Ricky"));  // nothing to erase
        cout << "Test case 11 passed"<<endl;
    }catch(...){
        cerr<<"Test failed at case 11"<<endl;
    }

    try{
        //#12 - 13 Change key and value type:OK
        test();
        //After change KeyType and ValueType and try once.
        cout << "Test case 12 - 13 passed"<<endl;
        cout << "Passed all tests" << endl;
    }catch(...){
        cerr<<"Test failed at case 12-13"<<endl;
    }

    return 0;
}