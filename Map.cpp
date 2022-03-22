//
// Created by Jun Kim on 2/22/22.
//
#include "Map.h"
#include <string>

int Convert_Key(string key)
//Check the value of each character which consists of the string variable
// depending on the ASCii table then return sum all of those value.
{
    string tempKey = key;
    int tempSize = tempKey.size();
    int tempAddress = 0;
    if (tempSize != 0){
        for (int i=0; i<tempSize; i++){
            tempAddress += tempKey[i];
        }
    }
    return tempAddress;
}

int Convert_Key(double key)
//Check the value of each character which consists of the double variable
// depending on the ASCii table then return sum all of those value.
{
    string tempKey = to_string(key);
    int tempSize = tempKey.size();
    int tempAddress = 0;
    if (tempSize != 0){
        for (int i=0; i<tempSize; i++){
            tempAddress += tempKey[i];
        }
    }
    return tempAddress;
}

Map::Map() {    //OK
//Construct hashtable filled with null pointers.
    for(int i=0; i<10; i++){
        hashtable[i] = nullptr;
    }
}

Map::Map(const Map &rhs) {  //OK
//Copy hashtable as reading pointers which consist in the hashtable
// from the rhs side and insert it to this hashtable.
    for (int i=0; i<10; i++){
        this->hashtable[i] = nullptr;
        if (rhs.hashtable[i] != nullptr){
            Hash *tempRhsPointer = rhs.hashtable[i];
            while(tempRhsPointer != nullptr) {
                this->insert(tempRhsPointer->key, tempRhsPointer->value);
                tempRhsPointer = tempRhsPointer->next;
            }
        }
    }
}

const Map &Map::operator=(const Map &rhs) {
//If rhs side is not empty, delete this hashtable and copy from rhs side.
//If rhs side is empty, just make empty this hashtable.
    if (!rhs.empty()){
        //delete this hashtable
        if (!this->empty()){
            for (int i=0; i<10; i++){
                if(this->hashtable[i] != nullptr){
                    while (this->hashtable[i] != nullptr){
                        Hash* tempDel = this->hashtable[i];
                        this->hashtable[i] = this->hashtable[i]->next;
                        delete tempDel;
                    }
                }
            }
        }
        //Copy Hash from rhs hashtable to this hashtable.
        for (int i=0; i<10; i++){
            if (rhs.hashtable[i] != nullptr){
                Hash *tempRhsPointer = rhs.hashtable[i];
                while(tempRhsPointer != nullptr) {
                    this->insert(tempRhsPointer->key, tempRhsPointer->value);
                    tempRhsPointer = tempRhsPointer->next;
                }
            }
        }
    }else{
        //delete this hashtable.
        if (!this->empty()){
            for (int i=0; i<10; i++){
                if(this->hashtable[i] != nullptr){
                    while (this->hashtable[i] != nullptr){
                        Hash* tempDel = this->hashtable[i];
                        this->hashtable[i] = this->hashtable[i]->next;
                        delete tempDel;
                    }
                }
            }
        }
    }
    return *this;
}

Map::~Map() {   //OK
//Delete all Hash existed in the hashtable.
    for (int i=0; i<10; i++){
        if(hashtable[i] != nullptr){
            while (hashtable[i] != nullptr){
                Hash* tempDel = hashtable[i];
                hashtable[i] = hashtable[i]->next;
                delete tempDel;
            }
        }
    }
}

bool Map::empty() const {   //Ok
//Check all indexes of the hashtable. If all of them are null pointers.
// return true or if it is not, return false.
    bool result = true;
    for (int i=0; i<10; i++){
        if (hashtable[i] != nullptr){
            result = false;
            break;
        }
    }
    return result;
}

int Map::size() const { //OK
//Count Hashes which has not a null pointer in the hashtable
// and return count value.
    int size = 0;
    for (int i=0; i<10; i++){
        Hash* temp = hashtable[i];
        while (temp != nullptr){
            size++;
            temp = temp->next;
        }
    }
    return size;
}

bool Map::insert(const KeyType &key, const ValueType &value) {  //OK
    //Find address which index will be used in the hash table.
    int tempAddress = Convert_Key(key) % 10;

    //insert data into the hash table
    //if the top of the hashtable points to the null pointer.
    //Make a new Hash and put data into the new Hash
    //then top of the hashtable points to the new Hash.
    //then return true
    if (hashtable[tempAddress] == nullptr){
        hashtable[tempAddress] = new Hash;
        hashtable[tempAddress]->key = key;
        hashtable[tempAddress]->value = value;
        hashtable[tempAddress]->next = nullptr;
        return true;
    }else{
    //If the top of the hashtable doesn't point to the null pointer
    //Find the pointer which has the null pointer at the next address
    //then Make a new Hash and put data into the new Hash
    //then top of the hashtable points to the new Hash.
    //then return true
        Hash* tempPointer = hashtable[tempAddress];
        while (tempPointer->next != nullptr && tempPointer->key != key){
            tempPointer = tempPointer->next;
        }
        if (tempPointer->key != key){
            tempPointer->next = new Hash;
            tempPointer->next->key = key;
            tempPointer->next->value = value;
            tempPointer->next->next = nullptr;
            return true;
        }
    }
    //If it fails to insert data, return false.
    return false;
}

bool Map::update(const KeyType &key, const ValueType &value) {  //OK
    //Find address which index will be used in the hash table.
    int  tempAddress = Convert_Key(key) % 10;

    //If the top of the hashtable points to the null pointer, return false.
    if (hashtable[tempAddress] == nullptr){
        return false;
    }else{
        //Search the Hash which has the same key as the key argument.
        Hash* tempPointer = hashtable[tempAddress];
        while (tempPointer->next != nullptr && tempPointer->key != key){
            tempPointer = tempPointer->next;
        }
        //If it finds the Hash, update the value with the value argument.
        //then return true;
        if (tempPointer->key == key){
            tempPointer->value = value;
            return true;
        }
    }
    //If it cannot find the Hash, returns false;
    return false;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value) {  //OK
    //First call the update function. If the update function works well, return true.
    //If it is not, call the insert function.
    //If everything fails, return false.
    if(this->update(key, value)){
        return true;
    }else{
        this->insert(key, value);
        return true;
    }
    return false;
}

bool Map::erase(const KeyType &key) {   //OK
    //Find address which index will be used in the hash table.
    int tempAddress = Convert_Key(key) % 10;

    //Search matched key value with the key argument.
    if (hashtable[tempAddress] != nullptr){
        Hash* tempPointer = hashtable[tempAddress];
        //if the key position is at the top of the hashtable, just delete it.
        if (tempPointer->key == key){
            hashtable[tempAddress] = hashtable[tempAddress]->next;
            delete tempPointer;
            return true;
        }
        Hash* tempPre = tempPointer;
        //if the key position is after the beginning of the hashtable,
        //finding the Hash with matching with the key argument.
        //Then delete it
        while (tempPointer != nullptr){
            if (tempPointer->key == key){
                tempPre->next = tempPointer->next;
                delete tempPointer;
                return true;
            }
            tempPre = tempPointer;
            tempPointer = tempPointer->next;
        }
    }
    //if it cannot the Hash which is matching with the key argument, return false.
    return false;
}

bool Map::contains(const KeyType &key) const {  //OK
    //Compare the keys which consist of the hashtable with the key argument.
    for(int i=0; i<10; i++){
        if (hashtable[i] != nullptr){
            Hash* tempPointer = hashtable[i];
            //If the matched key is on the top of the hashtable, return true.
            if (tempPointer->key == key){
                return true;
            }
            //If the matched key exists in the hashtable, return true.
            while (tempPointer != nullptr){
                if (tempPointer->key == key){
                    return true;
                }
                tempPointer = tempPointer->next;
            }
        }
    }
    //If the matched key doesn't exist, return false.
    return false;
}

bool Map::get(const KeyType &key, ValueType &value) const { //OK
    //Compare the keys which consist of the hashtable with the key argument.
    for(int i=0; i<10; i++){
        if (hashtable[i] != nullptr){
            Hash* tempPointer = hashtable[i];
            //If the matched key is on the top of the hashtable,
            //put the value of the pointer of the key to the value argument
            //then return true.
            if (tempPointer->key == key){
                value = tempPointer->value;
                return true;
            }
            //If the matched key exists in the hashtable,
            //put the value of the pointer of the key to the value argument
            //then return true.
            while (tempPointer != nullptr){
                if (tempPointer->key == key){
                    value = tempPointer->value;
                    return true;
                }
                tempPointer = tempPointer->next;
            }
        }
    }
    //If the matched key doesn't exist, return false.
    return false;
}

bool Map::get(int i, KeyType &key, ValueType &value) const {    //OK
    //Compare the position of the Hash with the i argument.
    if (i >= 0 && i < this->size()){
        int count = -1;
        for(int j=0; j<10; j++){
            if (hashtable[j] != nullptr){
                Hash* tempPointer = hashtable[j];
                while (tempPointer != nullptr && i != count){
                    count++;
                    //If the Hash exists at the position of i
                    //put the data of the pointer of the key and the value
                    //to the key and the value argument then return true.
                    if (i == count){
                        key = tempPointer->key;
                        value = tempPointer->value;
                        return true;
                    }
                    tempPointer = tempPointer->next;
                }
            }
        }
    }
    //If the Hash doesn't exist at the position of i, return false
    return false;
}

void Map::swap(Map &other) {    //OK
    //Swap the address between the index of the hashtable.
    for(int i=0; i<10; i++){
        Hash* tempPointer = other.hashtable[i];
        other.hashtable[i] = this->hashtable[i];
        this->hashtable[i] = tempPointer;
    }
}

bool combine(const Map& m1, const Map& m2, Map& result){
    bool result_bool = true;
    //If m1 is not equal with result
    if (m1.size() != result.size()){
        //Assign m1 to temp of the new Map
        Map temp = m1;
        //Insert data from m2 to temp.
        //If the function returns false, erase the Hash which has the same key
        // in temp and m2 from the temp.
        for(int i = 0; i < m2.size(); i++){
            KeyType key;
            ValueType value1, value2;
            m2.get(i,key,value1);
            if(!temp.insert(key,value1)){
                temp.get(key,value2);
                if (value1 != value2){
                    temp.erase(key);
                    result_bool = false;
                }
            }
        }
        //After finishing combine, swap the hashtable between result and temp.
        temp.swap(result);
    // m1 is equal with result and m2 is not equal with result
    }else if (m2.size() != result.size()){
        //Assign m2 to temp of the new Map
        Map temp = m2;
        //Insert data from m1 to temp.
        //If the function returns false, erase the Hash which has the same key in temp and m1
        //from the temp.
        for(int i = 0; i < m1.size(); i++){
            KeyType key;
            ValueType value1, value2;
            m1.get(i,key,value1);
            if(!temp.insert(key,value1)){
                temp.get(key, value2);
                if (value1 != value2){
                    temp.erase(key);
                    result_bool = false;
                }
            }
        }
        //After finishing combine, swap the hashtable between result and temp.
        temp.swap(result);
    // m1 is equal with result and m2 is equal with result too
    }else{
        if (m1.size() == result.size() && m2.size() == result.size()){
            //Check the value of the keys & the values of m1 & m2
            //if they are not exactly the same
            for (int i = 0; i < result.size(); i++){
                KeyType k1, k2, kr;
                ValueType v1, v2, vr;
                m1.get(i, k1, v1);
                m2.get(i, k2, v2);
                result.get(i, kr, vr);
                if ((k1 != kr || v1 != vr) || (k2 != kr || v2 != vr)){
                    result_bool = true;
                    break;
                }else{
                    result_bool = false;
                }
            }
            //Do the same procedure as if m1 is not equal with result
            if (result_bool){
                Map temp = m1;
                for(int i = 0; i < m2.size(); i++){
                    KeyType key;
                    ValueType value1, value2;
                    m2.get(i,key,value1);
                    if(!temp.insert(key,value1)){
                        temp.get(key,value2);
                        if (value1 != value2){
                            temp.erase(key);
                            result_bool = false;
                        }
                    }
                }
                temp.swap(result);
            }
        }
    }
    //If it finds as faulty, return false.
    return result_bool;
}

void subtract(const Map& m1, const Map& m2, Map& result){
    //Make a new Map
    Map temp;
    //check the key value between m1 and m2
    for (int i = 0; i < m1.size(); i++){
        KeyType k1, k2;
        ValueType v1, v2;
        bool ex_key = false;
        m1.get(i,k1,v1);
        for (int j = 0; j < m2.size(); j++){
            m2.get(j,k2,v2);
            //If the key doesn't exist in m1 & m2 at the same time
            if (k1 == k2){
                ex_key = true;
            }
        }
        //Put the Hash to temp hashtable
        if (!ex_key){
            temp.insert(k1, v1);
        }
    }
    //After finishing checking, swap temp with result
    temp.swap(result);
}




