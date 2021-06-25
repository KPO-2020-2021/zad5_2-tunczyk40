#include "Scena.hh"

Scena::Scena()
{

  Lacze.ZmienTrybRys(PzG::TR_3D);
  nr_elem = 0;
  nr_drona=0;
  Lacze.UstawZakresY(-300, 300);
  Lacze.UstawZakresX(-300, 300);
  Lacze.UstawZakresZ(-300, 300);

  double tab_wym[3] = {600, 600, 0};
  Wektor3D wym_dna(tab_wym);
  dno = new Plaszczyzna(wym_dna, 20);
  Wektor3D srod;
  for(int i=0; i<4; i++)
  {
  srod[0] = rand() % 400 - 200;
  srod[1] = rand() % 400 - 200;
  srod[2] = 50;
  int nr_p=rand()%3;
   if(nr_p==0)
  Lista_elementow.push_front(std::make_shared<Gora>(srod, 100, 50, 100, "../datasets/Element" + std::to_string(nr_elem) + ".dat"));
 else if(nr_p==1)
  Lista_elementow.push_front(std::make_shared<Plaskowyz>(srod, 100, 50, 100, "../datasets/Element" + std::to_string(nr_elem) + ".dat"));
   else if(nr_p==2)
  Lista_elementow.push_front(std::make_shared<Gran>(srod, 100, 50, 100, "../datasets/Element" + std::to_string(nr_elem) + ".dat"));
  nr_elem++;
  }
  for (std::list<std::shared_ptr<Bryla>>::const_iterator a = Lista_elementow.begin(); a != Lista_elementow.end(); a++)
  {
    Lacze.DodajNazwePliku((*a)->get_nazwa().c_str());
    (*a)->zapisz();
  }

  Lacze.DodajNazwePliku(dno->get_nazwa().c_str());
  dno->zapisz();
  for (int i = 0; i < N; i++)
  {
    double pozycja[3] = {(double)(rand() % 440 - 220), (double)(rand() % 440 - 220), 25};
    Lista_Dronow.push_front(std::make_shared<Dron>(i, Lacze, Wektor3D(pozycja))) ;
    (*Lista_Dronow.begin())->zapisz();
    nr_drona++;
  }

  Lacze.Rysuj();
}
void Scena::rysuj()
{

  Lacze.Rysuj();
}
bool Scena::interfejs()
{
  cout << "1.Drony, 2. dodaj element, 3 usun element,4 usun drona" << endl;
  int opcja;
  cin >> opcja;
  switch (opcja)
  {
  case 1:
  {
    cout << "podaj nr " << endl;
    for(int i=0; i<(int)Lista_Dronow.size(); i++)
    {
      cout<<i <<" ";
    }
    cout<<":"<<endl;
    int nr;
    cin >> nr;
    std::list<std::shared_ptr<Dron>>::const_iterator a;
    a=Lista_Dronow.begin();
    for(int i=0; i<nr; i++)
    {
      a++;
    }
    
    (*a)->sterowanie();
  }
  break;
  case 2:
  {
    cout << "podaj 1-gora, 2-plaskowyz, 3 gran, 4 dron" << endl;

    int nr;
    cin >> nr;
    Wektor3D srod;

    srod[0] = rand() % 400 - 200;
    srod[1] = rand() % 400 - 200;
    srod[2] = 50;

if( nr!=4)
{
    if (nr == 1)
    {

      Lista_elementow.push_front(std::make_shared<Gora>(srod, 100, 50, 100, "../datasets/Element" + std::to_string(nr_elem) + ".dat"));
    }
    if (nr == 2)
    {

      Lista_elementow.push_front(std::make_shared<Plaskowyz>(srod, 100, 50, 100, "../datasets/Element" + std::to_string(nr_elem) + ".dat"));
    }
    if (nr == 3)
    {

      Lista_elementow.push_front(std::make_shared<Gran>(srod, 100, 50, 100, "../datasets/Element" + std::to_string(nr_elem) + ".dat"));
    }
    nr_elem++;
    (*Lista_elementow.begin())->zapisz();
    Lacze.DodajNazwePliku((*Lista_elementow.begin())->get_nazwa().c_str());
}
else
{
  double pozycja[3] = {(double)(rand() % 440 - 220), (double)(rand() % 440 - 220), 25};
  Lista_Dronow.push_front(std::make_shared<Dron>(nr_drona, Lacze, Wektor3D(pozycja)));
  (*Lista_Dronow.begin())->zapisz();
}
  }
  break;
  case 3:
  {
    int i = 0;
    for (std::list<std::shared_ptr<Bryla>>::const_iterator a = Lista_elementow.begin(); a != Lista_elementow.end(); a++)
    {
      cout << i << ": " << (*a)->get_nazwa() << endl;
      i++;
    }
    cout << "podaj numer" << endl;

    int nr;
    cin >> nr;
    std::list<std::shared_ptr<Bryla>>::const_iterator a = Lista_elementow.begin();

    for (int j = 0; j < nr; j++)
    {

      a++;
    }
    
    Lacze.UsunNazwePliku((*a)->get_nazwa());
    Lista_elementow.erase(a);
  }
  break;
  ////faza 3 dla niektórych///
    case 4:
  {
    int i = 0;
    for (std::list<std::shared_ptr<Dron>>::const_iterator a = Lista_Dronow.begin(); a != Lista_Dronow.end(); a++)
    {
      cout << i << ": " << (*a)->get_id() << endl;
      i++;
    }
    cout << "podaj numer" << endl;

    int nr;
    cin >> nr;
    std::list<std::shared_ptr<Dron>>::const_iterator a = Lista_Dronow.begin();

    for (int j = 0; j < nr; j++)
    {

      a++;
    }
    
   (*a)->usun();
    Lista_Dronow.erase(a);
  }
  break;

  default:
    break;
  }

  return true;
}

Scena::~Scena()
{
  free(dno);

}