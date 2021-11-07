#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
class Point{
    public:
    	float x,y;
        Point();
        Point(float,float);
        void Print_Point();
};
Point::Point()
{
    x=y=0;
}
Point::Point(float a,float b)
{
    x=a;
    y=b;
}
void Point::Print_Point()
{
    cout<<"( "<<setprecision(2)<<x<<" , "<<setprecision(2)<<y<<" )";
}

class Side{
    Point* P1;
	Point* P2;
    public:
        Side();
        Side(Point* p1,Point* p2);
        Side(const Side &obj);
        float Length();
        void Print_Side();
        float slope();
        bool Is_Parallel(Side s);
        bool Is_Perpendicular(Side s);
};
Side::Side()
{
    P1=nullptr;
    P2=nullptr;
}
Side::Side(Point* p1,Point* p2)
{
    P1=p1;
    P2=p2;
}
Side::Side(const Side &obj)
{
	P1=obj.P1;
	P2=obj.P2;
}
float Side::slope()
{
    return (P2->y - P1->y) / (P2->x - P1->x);
}
float Side::Length()
{
    return sqrt(pow((P2->x - P1->x),2) + pow((P2->y - P1->y),2));
}
void Side::Print_Side()
{
    P1->Print_Point();
    cout<<" to ";
    P2->Print_Point();
}
bool Side::Is_Parallel(Side s)
{
    auto s_slope=s.slope();
    auto this_slope=this->slope();
    if(isinf(s_slope)&&isinf(this_slope))
        return true;
    else if(isinf(s_slope)||isinf(this_slope))
        return false;
    else
        return this_slope==s_slope;
}
bool Side::Is_Perpendicular(Side s)
{
    auto s_slope=s.slope();
    auto this_slope=this->slope();
    if( (this_slope==0 && isinf(s_slope)) || (s_slope==0 && isinf(this_slope)))
        return true;
    else if(isinf(s_slope) || isinf(this_slope))
        return false;
    else
        return this_slope*s_slope == -1 ;
}

int main()
{
    float x,y;
    vector<Point> points;
    int num=0;
    while(num!=1)
    {
        cout<<"Enter x for the point\n";
        cin>>x;
        cout<<"Enter y for the point\n";
        cin>>y;
        Point p(x,y);
        points.push_back(p);
        puts("Enter 1 if you want to stop entering points. Else enter any number to continue");
        cin>>num;
    }
    vector<Point> test;
    for(auto i=0;i<points.size();++i)
    {
        test.push_back(points[i]);
        for(auto j=i+1;j<points.size();++j)
        {
            test.push_back(points[j]);
            for(auto k=j+1;k<points.size();++k)
            {
                test.push_back(points[k]);
                for(auto l=k+1;l<points.size();++l)
                {
                    test.push_back(points[l]);
                    vector<Side> rect;
                    for(auto a=0;a<test.size()-1;++a)
                    {
                        Side s(&test[a],&test[a+1]);  
                        rect.push_back(s);
                    }
                    Side s(&test[3],&test[0]);
                    rect.push_back(s);
                    Side s1(&test[0],&test[2]);
                    rect.push_back(s1);
                    Side s2(&test[1],&test[3]);
                    rect.push_back(s2);
                    Side side1,side2;
                    bool is_rect=false;
                    for(auto a=0;a<rect.size();++a)
                    {
                        if(is_rect)
                            break;
                        for(auto b=a+1;b<rect.size();++b)
                        {
                            if(rect[a].Is_Parallel(rect[b]))
                            {
                                side1=rect[a];
                                side2=rect[b];
                                is_rect=true;
                                break;
                            }
                        }
                    }
                    if(!is_rect)
                    {
                        test.pop_back();
                        continue;
                    }
                    Side side3,side4;
                    int count=0;
                    for(auto a=0;a<rect.size();++a)
                    {
                    	if(count>2)
                    		break;
                        if(side1.Is_Perpendicular(rect[a]))
                        {
                            if(count == 0)
                            {
                                side3=rect[a];
                            }
                            if(count == 1)
                            {
                               	side4=rect[a];
                            }
                            ++count;
                        }
                    }
                    if(count!=2)
                    {
                        test.pop_back();
                        continue;
                    }
                    cout<<"These points form a rectangle\n";
                    for(auto a=0;a<test.size();++a)
                    {
                        test[a].Print_Point();
                        puts("");
                    }
                    rect.clear();
                    test.pop_back();
                }
                test.pop_back();
            }
            test.pop_back();
        }
        test.pop_back();
    }
    return 0;
}
