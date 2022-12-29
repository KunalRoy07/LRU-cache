#include<iostream>
#include<unordered_map>
#include<list>
using namespace std;

class Node
{
    public:
    string key;
    int value;
    Node(string key,int value)
    {
        this->key=key;
        this->value=value;
    }
};

class LRUcache
{
    public:
    int maxsize;
    list<Node> l;
    unordered_map<string,list<Node>::iterator> m;
    LRUcache(int maxsize)
    {
       this->maxsize=maxsize >1 ? maxsize : 1;
    }

    void insertKeyValue(string key,int value)
    {
        //2 cases
        // present inside the cache
        if(m.count(key)!=0)
        {
            //replace the old value and update
            auto it=m[key];
            it->value=value;
            
        }
        else{
            //check if the cache is full or not
            /* remove the least reacently used item from the cache*/
            if(l.size()==maxsize)
            {
                Node last=l.back();
                m.erase(last.key);
                l.pop_back();
            }
            //now the sapce is created in the cache
            //now we can insert the new node

            Node n(key,value);
            l.push_front(n); //inserting the node to the front of the list
            m[key]=l.begin();
        }
    }

    int* getValue(string key)
    {
        //first check whether the key is present inside the cache or not
        if(m.count(key)!=0)
        {
            auto it=m[key];
            int value=it->value;
            l.push_front(*it);
            l.erase(it);
            m[key]=l.begin();
            return &l.begin()->value;
        }
        return NULL;

    }
    string mostRecentKey()
    {
        return l.front().key;
    }
};

int main()
{
    LRUcache lru(3);
    lru.insertKeyValue("Mango",10);
    lru.insertKeyValue("Apple",20);
    lru.insertKeyValue("Guava",30);
    cout<<lru.mostRecentKey()<<endl;

    lru.insertKeyValue("Mango",40);
    cout<<lru.mostRecentKey()<<endl;

    int* orders=lru.getValue("Mango");
    if(orders!=NULL)
    {
        cout<<"order of mango : "<<*orders<<endl;
    }
    lru.insertKeyValue("Banana",20);
    
    if(lru.getValue("Apple")==NULL)
    {
        cout<<"Apple do not exist";
    }

    if(lru.getValue("Guava")==NULL)
    {
        cout<<"Guava do not exist";
    }

    if(lru.getValue("Banana")==NULL)
    {
        cout<<"Banana do not exist";
    }

    if(lru.getValue("Mango")==NULL)
    {
        cout<<"Mango do not exist";
    }
    return 0;
}