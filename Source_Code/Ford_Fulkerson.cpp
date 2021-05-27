#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <algorithm>
#include <list>
#include <vector>
#include <map>

struct wezel{
    wezel* nast;
    int end;
    int flow;
    int capacity;
};

enum Colour {GRAY,WHITE,BLACK};


int main() {
    std::fstream problem;
    problem.exceptions(std::fstream::failbit);
    try {
        problem.open("graf.json");
    }catch(const std::fstream::failure &f){
        std::cerr << "Wczytywanie pliku nie powiodlo sie. Plik musi byc w tym samym katalogu co plik exe";
        getchar();
        exit(1);
    }

    int l_w;
    int w_pocz, w_kon;
    int max_flow=0;
    bool is_it;

    std::vector<wezel*> Lista;
    std::map<std::string,int> nodes;

    char c;
    problem.get(c);
    if(c == '['){
        std::string str;
        std::stringstream ss;
        wezel* x=nullptr;
        problem.get(c);
        while(c=='['){
            std::string pocz;
            std::string kon;
            x = new wezel;
            getline(problem,str,']');
            std::replace(str.begin(),str.end(),',',' ');
            ss<<str;
            ss>>pocz;
            if(nodes.find(pocz)==nodes.end()){
                nodes[pocz]=Lista.size();
                Lista.push_back(nullptr);
            }
            ss>>kon;
            if(nodes.find(kon)==nodes.end()){
                nodes[kon]=Lista.size();
                Lista.push_back(nullptr);
            }
            x->end=nodes[kon];
            ss>>x->capacity;
            x->flow=0;
            x->nast=Lista[nodes[pocz]];
            Lista[nodes[pocz]]=x;
            problem.get(c);
            problem.get(c);
            problem.get(c);
            ss.clear();
        }
    }
    std::string str;
    problem>>str;
    if(nodes.find(str)==nodes.end()){
        std::cerr << "Nie ma takiego zrodla\n";
        getchar();
        exit(2);
    }
    w_pocz=nodes[str];
    str.clear();
    problem>>str;
    if(nodes.find(str)==nodes.end()){
        std::cerr<< "Nie ma takiego konca przeplywu\n";
        getchar();
        exit(3);
    }
    w_kon=nodes[str];
    problem.close();

    l_w=Lista.size();
    auto Parent = new int [l_w];
    auto Capacity = new int [l_w];
    auto Shade = new Colour [l_w];

    for(int i=0;i<l_w; i++)
        for(auto x = Lista[i];x;x=x->nast){
            is_it=false;
            for(auto y = Lista[x->end];y;y=y->nast)
                if(y->end==i){
                    is_it=true;
                    break;
                }
            if(!is_it){
                auto sztuczny = new wezel;
                sztuczny->flow=sztuczny->capacity=0;
                sztuczny->end=i;
                sztuczny->nast=Lista[x->end];
                Lista[x->end]=sztuczny;
            }
        }

    std::list<int> kolejka;
    while(1) {
        for (int i = 0; i < l_w; i++)
            Parent[i] = NULL;
        Parent[w_pocz] = NULL;

        for (int i=0; i<l_w; i++)
            Shade[i]=WHITE;
        Shade[w_pocz]=GRAY;
        Capacity[w_pocz]=INT_MAX;
        kolejka.clear();
        kolejka.push_front(w_pocz);
        while(!kolejka.empty()){
            is_it = false;
            int cur = kolejka.front();
            kolejka.pop_front();
            for(auto x = Lista[cur]; x; x=x->nast){
                int flow = x->capacity - x->flow;
                if(!flow || (Shade[x->end]!=WHITE))
                    continue;
                Parent[x->end]=cur;
                Capacity[x->end]=flow>Capacity[cur]?Capacity[cur]:flow;


                if(x->end==w_kon){
                    is_it=true;
                    break;
                }
                else kolejka.push_back(x->end);
            }
            Shade[cur]=BLACK;
            if(is_it) break;
        }
        if(!is_it) break;

        max_flow += Capacity[w_kon];
        int cur = Parent[w_kon];
        int prev=w_kon;
        while(prev!=w_pocz){
            for(auto x=Lista[cur];x;x=x->nast)
                if(x->end==prev){
                    x->flow+=Capacity[w_kon];
                    break;
                }
            for(auto x=Lista[prev];x;x=x->nast)
                if(x->end==cur){
                    x->flow-=Capacity[w_kon];
                    break;
                }
            prev=cur;
            cur=Parent[cur];
        }
    }

    std::cout<<"max flow: " << max_flow << '\n' << std::endl;

    std::map<int,std::string> r_nodes;
    for(auto it = nodes.begin(); it!=nodes.end(); it++)
        r_nodes[it->second]=it->first;

    for(int i=0;i<l_w;i++){
        for(auto x = Lista[i];x;x=x->nast){
            if(x->capacity){
                if(x->flow<0)
                    std::cout << r_nodes[i] << "->" << r_nodes[x->end] << ": " <<  0 << "/" << x->capacity << std::endl;
                else
                    std::cout << r_nodes[i] << "->" << r_nodes[x->end] << ": " <<  x->flow << "/" << x->capacity << std::endl;
            }

        }
    }


    for(int i=0;i<l_w;i++){
        auto x = Lista[i];
        while(x){
            wezel* z = x;
            x=x->nast;
            delete z;
        }
    }
    delete [] Parent;
    delete [] Capacity;
    getchar();
    return 0;
}