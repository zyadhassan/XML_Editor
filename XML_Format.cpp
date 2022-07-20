#include"XML.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stack>
using namespace std;


    void Node::setvalue(string v) {
        value = v;
    }

    void Tree:: setroot(Node* t) {
        m_root = t;
    }
    void Tree::addNode(Node* node, Node* parent) {
        if (parent == nullptr)
        {
            parent = m_root;
        }
        parent->children.push_back(node);
    }

    string Tree::format(int depth = 0, Node* parent = nullptr)
    {
        bool f=false;
        if (parent == nullptr)
        {
            parent = m_root;
            depth = 0;
        }
        string output = "";
        for (  unsigned long long i = 0; i < parent->children.size(); ++i)
        {
            Node* node = parent->children[i];

            string indentation = "";

            // indentation value
            for (int i = 0; i < depth; ++i)
            {
                indentation += "    ";
            }
            //////////////////////////////////
            if (node->children.size() > 0)
            {
                 output += indentation + "<" + node->key + ">\n"; // <name>
            }
            else
            {
                // insert value
                output += indentation + "<" + node->key + ">"; // <name>
            }
            /////////////////////////////////
            // insert key open
           // output += indentation + "<" + node->key + ">\n"; // <name>

            if (node->children.size() > 0)
            {
                output += format(depth + 1, node);
            }
            else
            {
                // insert value
                output += node->value+"</" + node->key + ">\n" ;


               // output +=  "</" + node->key + ">\n";// </name>
                f=true;
            }
            //close the key

         if(!f)output += indentation + "</" + node->key + ">\n";// </name>
        }
        return output;
    }


Tree Parsing(string g) {
    stack <Node*> stk;
    unsigned int h = g.find("<", 0), j;
    if (g.substr(h + 1, 1) == "?") {
        j = g.find(">", h);
        g.erase(h, j - h + 1);
    }
    string firsttag;
    unsigned long long  st = 0, ps;
   //  unsigned long long o, v;
    st = g.find("<", st);
    ps = g.find(">", st);
    firsttag = g.substr(st + 1, ps - st - 1);
    Node* root = new Node;
    Node* node = new Node;
    node->key = firsttag;
    Tree  y;
    y.setroot(root);
    y.addNode(node, root);
    st = g.find("<", ps);
    ps = g.find(">", st);
    Node* parent = node;
    while (g.find("<", ps) != string::npos) {
        if (g.substr(st + 1, 1) != "/") {
            Node* newnode = new Node;
            newnode->key = g.substr(st + 1, ps - st - 1);
            st = g.find("<", ps);
            y.addNode(newnode, parent);
            if (st != string::npos) {

                newnode->value = g.substr(ps + 1, st - ps - 1);
                if (g.substr(st + 1, 1) != "/") {
                    stk.push(parent);
                    parent = newnode;

                }
            }
            ps = g.find(">", st);
        }
        if (g.substr(st + 1, 1) == "/") {
            st = g.find("<", ps);
            ps = g.find(">", st);
            if (st != string::npos) {
                if (g.substr(st + 1, 1) == "/") {
                    if (!stk.empty())
                    {
                        parent = stk.top();
                        stk.pop();
                    }

                }
            }
        }

    }
    return y;
}
string XML_Format(string str){
    Tree tr = Parsing(str);
    return tr.format();
}

string read(string path) {
    string xml;
    string tmp;
    string filepath=path;
    fstream file;
    file.open(filepath, ios::in);
    while (file >> xml)
    {
        for (int i = 0; i < xml.length(); i++)
        {
            tmp += xml[i];
        }
    }
    return  tmp;
}
Tree network(string g) {
    Tree y;
    Node* root = new Node;
    y.setroot(root);
    Node* parent = root;
    int st = 0, ps = 0;
    int x = 0;
    string tag;
    while (g.find("<", ps) != string::npos) {
        if (st != string::npos) {
            st = g.find("<", ps);
            ps = g.find(">", st);
            tag = g.substr(st + 1, ps - st - 1);
        }
        if (tag == "id") {
             Node* c = new Node;
                st = g.find("<", ps);
                c->key = tag;
                c->value = g.substr(ps + 1, st - ps - 1);
                y.addNode(c, parent);
                if (x == 0) {
                    parent = c;
                    x++;
                }
            }
             if (tag == "/followers") {
                x = 0;
                parent = root;
    }
    }
    return y;

}

Tree parse(string g) {
    stack <Node*> stk;
    unsigned int h = g.find("<", 0), j;
    if (g.substr(h + 1, 1) == "?") {
        j = g.find(">", h);
        g.erase(h, j - h + 1);
    }
    string firsttag;
    unsigned int st = 0, ps;
    unsigned int o, v;
    st = g.find("<", st);
    ps = g.find(">", st);
    firsttag = g.substr(st + 1, ps - st - 1);
    Node* root = new Node;
    Node* node = new Node;
    node->key = firsttag;
    Tree  y;
    y.setroot(root);
    y.addNode(node, root);
    st = g.find("<", ps);
    ps = g.find(">", st);
    Node* parent = node;
    while (g.find("<", ps) != string::npos) {
        if (g.substr(st + 1, 1) != "/") {
            Node* newnode = new Node;
            newnode->key = g.substr(st + 1, ps - st - 1);
            st = g.find("<", ps);
            y.addNode(newnode, parent);
            if (st != string::npos) {
                newnode->value = g.substr(ps + 1, st - ps - 1);
                if (g.substr(st + 1, 1) != "/") {
                    stk.push(parent);
                    parent = newnode;

                }
            }
            ps = g.find(">", st);
        }
        if (g.substr(st + 1, 1) == "/") {
            st = g.find("<", ps);
            ps = g.find(">", st);
            if (st != string::npos) {
                if (g.substr(st + 1, 1) == "/") {
                    if (!stk.empty())
                    {
                        parent = stk.top();
                        stk.pop();
                    }

                }
            }
        }

    }
    return y;
}




string visual(string r)
{
   // string z = read();
    Tree  tr = network(r);
    string out = "digraph test {\n";
    for (int i = 0; i < tr.m_root->children.size(); i++) {
        for (int j = 0; j < tr.m_root->children[i]->children.size(); j++) {
            out += tr.m_root->children[i]->value + "->" + tr.m_root->children[i]->children[j]->value + '\n' ;
        }
    }
    out += "}";
     cout <<out;
    return out;
}
