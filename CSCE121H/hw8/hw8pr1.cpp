#include "std_lib_facilities_4.h"

// DONE Modify Link class from 17.10.1 to hold value of struct God.
// DONE God has members of type string: name, mythology, vehicle, weapon
// DONE Write print_all() function that lists gods with attributes one per line
// DONE Add member function add_ordered() that places new element in correct lexicographical position
// Using Links with values of type God, make list of gods from three mythologies, then move elements (gods) from that list to three lexicographically ordered lists - one for each mythology


struct God
{
	string name;
	string myth;
	string vehicle;
	string weapon;
	
	God(const string& n,const string& m, const string& v, const string& w,God* p = nullptr, God*  = nullptr):name(n),myth(m),vehicle(v),weapon(w){}
};

struct Link
{
private:
	Link* prev;
	Link* succ;
public:
	God god;
	
	Link(God g,Link* p = 0,Link* s = 0):god(g),prev(p),succ(s){}
	
	Link* add_ordered(Link* p,Link* n) // "old" is the "all_gods" list
		{
			while(n != 0 && p != 0 && n->god.name < p->god.name)
			{
				p = p->next();
			}
			if (p==nullptr) return n;
			if (n==nullptr) return p;	
			n->succ = p;
			if(p->prev) p->prev->succ = n;
			n->prev = p->prev;
			p->prev = n;
			return n;
		}
		
	void print_all(Link* n)
		{
			while(n)
			{
				cout << "My name is " << n->god.name << "." << endl;
				cout << "I am " << n->god.myth << "." << endl;
				cout << "I transport in my " << n->god.vehicle << "." << endl;
				cout << "I use my " << n->god.weapon << " to fight." << endl;
				cout << " " << endl;
				if(n=n->next()) cout << "";
			}
		}
	
	Link* next() const {return succ; }
	Link* previous() const {return prev;}	
	
	Link* find(Link* god,Link* list)
		{
			while(list)
			{
				if(list = god) return god;
				list = list->succ;
			}
			return god;
		}
		
	Link* erase(Link* god)
		{
			if(god==nullptr) return nullptr;
			if(god->succ) god->succ->prev = god->prev;
			if(god->prev) god->prev->succ = god->succ;
			return god->succ;
		}
};

int main()
{
	try
	{
		cout << "gods work" << endl;
		God thor("Thor","Avenger","Corvette","Sword");
		God athena("Athena","Greek","Unicorn","Brain");
		God zeus("Zeus","Greek","Mustang","Pistol");
		God nobody("Nobody","Has No classification","Car","Weapon");
		
		cout << "all_gods works" << endl;
		Link* all_gods = all_gods->add_ordered(all_gods,new Link(thor));
		all_gods->add_ordered(all_gods,new Link(athena));
		all_gods->add_ordered(all_gods,new Link(zeus));
		all_gods->add_ordered(all_gods,new Link(nobody));
		
		cout << "adding to new lists works" << endl;
		Link* greek_gods = greek_gods->add_ordered(greek_gods,new Link(athena));
		Link* norse_gods = norse_gods->add_ordered(norse_gods,new Link(zeus));
		Link* other_gods = other_gods->add_ordered(other_gods,new Link(thor));
		
		cout << "erasing from old list works" << endl;
		all_gods->erase(greek_gods);
				
		cout << "printing all gods works" << endl;
		all_gods->print_all(all_gods);
	}
	catch(exception& e)
	{
		cerr << "exception: " << e.what() << endl;
	}
	catch(...)
	{
		cerr << "Something went wrong" << endl;
	}
}