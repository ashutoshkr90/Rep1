#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<algorithm>
#include<vector>
#include<cmath> 
#define pi 3.141592653589793
#define earthRadiusKm 6378
#define large_val 1000000
#define maxn 100
#define maxm 300
#define maxq 10000

using namespace std;

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */ 
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) 
{
  double lat1r, lon1r, lat2r, lon2r,distance;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
 
  distance = earthRadiusKm * acos (sin (lat1r) * sin(lat2r) + cos(lat1r) * cos(lat2r) * cos(lon1r - lon2r));
  
  //Rounding to next integer
  return (int) (distance + 0.5);  
}


int main()
{
	
	double dis[maxn][maxn]; // distance between two cities
    pair<double,double> city_cord [maxn];
    map<string, int> city_id;

    bool t= true; 
    int cases = 1;
    
    while(t)
    {
        int n,m,q;  //n->number of cities, m->number of direct flights, q->number of queries
        cin>>n>>m>>q;
       
        if ((n==0) && (m==0) &&(q==0))
        break;      
        
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        if(i!=j)
        dis[i][j]=large_val;
        else
        dis[i][j]=0;        
        
        for(int i=0;i<n;i++)  //take the input city and its location
        {
            string city_name;
            cin>>city_name;
            double a,b;
            cin>>a>>b;
            city_cord[i]=make_pair(a,b);
            city_id[city_name]=i;
        }
		
        for(int i=0;i<m;i++)  // direct flights
        {
            string a,b;
            cin>>a>>b;
            int citystart = city_id[a];
            int cityend = city_id[b];
             dis[city_id[a]][city_id[b]]= distanceEarth(city_cord [citystart].first, city_cord [citystart].second, city_cord [cityend].first, city_cord [cityend].second);
	    }
        

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                   if (dis[i][k] + dis[k][j] < dis[i][j])
                     dis[i][j] = dis[i][k] + dis[k][j];
                   
                }
            }
        }
        
        cout<<"Case #"<< cases++ <<endl;
        
        for(int i=0;i<q;i++) //queries
        {
            string a,b;
            cin>>a>>b;
            double dist= dis[city_id[a]][city_id[b]];
            if(dist<large_val)
            cout<< dist <<" Km" <<endl;
            else
            cout<<"no route exists"<<endl;
        }        
        cout<<endl;
    }
	
    return 0;
}