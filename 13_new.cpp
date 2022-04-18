#include <bits/stdc++.h>
using namespace std;

class Page
{
    public:
        int pagesize;
        //vector<Record> records;
        //vector<int> address;

        //map<int,int> records
        vector<int> records;
        int recordCount;
        int freespace;
        vector<int>::iterator lastaddress;

        Page* next;
        Page* prev;

    Page(int pagesize)
    {
        this->pagesize=pagesize;
        next=NULL;
        prev=NULL;
        recordCount=0;
        freespace=pagesize - 16;
    }

};

class Heap
{
public:
    Page* head;
    Page* tail;
    int psize;
    int pagesCount;

    Heap(int psize)
    {
        head=NULL;
        tail=NULL;
        pagesCount=0;
        this->psize=psize;
    }

    void insert(int rsize,int primary_key)
    {
        //find the first page that can accomodate the record
        //if none then create new one
        Page* page=head;
        while(page!=NULL)
        {
            if(page->freespace >= (rsize+4))
            {
                break;
            }
            page=page->next;
        }

        if(page==NULL)
        {
            //create new page
            page= new Page(psize);
            if(tail!=NULL)
            {
                tail->next= page;
                page->prev= tail;
                tail=page;
            }
            else
            {
                head=page;
                tail=page;
            }
            pagesCount++;
        }

        page->records.push_back(primary_key);
        page->freespace= page->freespace - rsize - 4;
        page->recordCount++;
        page->lastaddress=page->records.end()-1;
    }

    void search(int key)
    {
        Page* p=head;
        int i=0;
        while(p!=NULL)
        {
            vector<int> &m= p->records;
            int j;
            for(j=0;j<m.size();j++)
            {
                if(m[j]==key)
                {
                    break;
                }
            }

            if(j<m.size())
            {
                cout<<i<<" "<<j<<endl;
                return;
            }
            p=p->next;
            i++;
        }

        cout<<"-1 -1\n";
    }

    void display()
    {
        cout<<pagesCount<<" ";

        Page* p=head;
        while(p!=NULL)
        {
            cout<<p->recordCount<<" ";
            p=p->next;
        }
        cout<<endl;
    }

};

int main()
{
    int psize;
    cin>>psize;

    Heap h(psize);
    int choice;
    int rsize, key;
    do
    {
        cin>>choice;
        if(choice==1)
        {
            cin>>rsize>>key;
            h.insert(rsize,key);
        }
        else if(choice==3)
        {
            cin>>key;
            h.search(key);
        }
        else if(choice==2)
        {
            h.display();
        }
    } while(choice!=4);

}
