#ifndef _Q_ROLE_INFO_H
#define _Q_ROLE_INFO_H
               
#include <vector>
#include <map>
#include <iostream>
#include <string>

using std::string;
using std::vector;
using std::map;

//>=======================================================
/*
* classname   Q_role_infoBean
* description  E:\workspace\game-code\excel\hoopchina.xls
**/
class Q_role_infoBean
{    
public:
    /*
    * description  get ID
    **/
    int getQ_id() const
    //
    /*
    * description  set ID
    **/
    void setQ_id(int _q_id)
    /*
    * description  get 名字
    **/
    string getQ_name() const
    //
    /*
    * description  set 名字
    **/
    void setQ_name(string _q_name)
    /*
    * description  get 性别
    **/
    int getQ_sex() const
    //
    /*
    * description  set 性别
    **/
    void setQ_sex(int _q_sex)
    /*
    * description  get 家庭住址
    **/
    string getQ_home_addr() const
    //
    /*
    * description  set 家庭住址
    **/
    void setQ_home_addr(string _q_home_addr)
    /*
    * description  get 婚姻状况
    **/
    bool getQ_marriage() const
    //
    /*
    * description  set 婚姻状况
    **/
    void setQ_marriage(bool _q_marriage)
private:
    int q_id;
    string q_name;
    int q_sex;
    string q_home_addr;
    bool q_marriage;
};

//>-------------------------------------------------------
//description  get ID
int Q_role_infoBean:: getQ_id() const
{
    return this->q_id;
}

//>-------------------------------------------------------
//description  set ID
void Q_role_infoBean:: setQ_id(int _q_id)
{
    this->q_id = _q_id;
}

//>-------------------------------------------------------
//description  get 名字
string Q_role_infoBean:: getQ_name() const
{
    return this->q_name;
}

//>-------------------------------------------------------
//description  set 名字
void Q_role_infoBean:: setQ_name(string _q_name)
{
    this->q_name = _q_name;
}

//>-------------------------------------------------------
//description  get 性别
int Q_role_infoBean:: getQ_sex() const
{
    return this->q_sex;
}

//>-------------------------------------------------------
//description  set 性别
void Q_role_infoBean:: setQ_sex(int _q_sex)
{
    this->q_sex = _q_sex;
}

//>-------------------------------------------------------
//description  get 家庭住址
string Q_role_infoBean:: getQ_home_addr() const
{
    return this->q_home_addr;
}

//>-------------------------------------------------------
//description  set 家庭住址
void Q_role_infoBean:: setQ_home_addr(string _q_home_addr)
{
    this->q_home_addr = _q_home_addr;
}

//>-------------------------------------------------------
//description  get 婚姻状况
bool Q_role_infoBean:: getQ_marriage() const
{
    return this->q_marriage;
}

//>-------------------------------------------------------
//description  set 婚姻状况
void Q_role_infoBean:: setQ_marriage(bool _q_marriage)
{
    this->q_marriage = _q_marriage;
}


//>=======================================================
/*
* classname   Q_role_infoContainer
* description  E:\workspace\game-code\excel\hoopchina.xls
**/
class Q_role_infoDao : public BaseDao
{
public:
    Q_role_infoDao();
    vector<Q_role_infoBean*>* select();
private:
    SqlSessionFactory *factory_;
};

Q_role_infoDao : Q_role_infoDao()
{
    factory = getFactory();
}

vector<Q_role_infoBean*>* Q_role_infoDao::select()
{
    vector<Q_role_infoBean*> *list = NULL;
    SqlSession *session = this->factory_->openSession();
    list = session->selectList<Q_role_info>("q_role_info.select");
    session->close();
    return list;
}

//>=======================================================
/*
* classname   Q_role_infoContainer
* description  E:\workspace\game-code\excel\hoopchina.xls
**/
class Q_role_infoContainer
{    
public:
    Q_role_infoContainer();
    const vector<Q_role_infoBean*>& getList()const;
    const map<<int, Q_role_infoBean*>& getMap()const
    void load();
private:
    vector<Q_role_infoBean*> *list;
    map<<int, Q_role_infoBean*> map;
    Q_role_infoDao *dao;
};

//>-------------------------------------------------------          
Q_role_infoContainer:Q_role_infoContainer()
{
    this->list = NULL;
    this->dao = new Q_role_infoDao();
}

//>-------------------------------------------------------
//description  getList
const vector<Q_role_infoBean*>& Q_role_infoContainer:: getList()const;
{
    return this->list;
}

//>-------------------------------------------------------
//description  set ID
const map<int, Q_role_infoBean*>& Q_role_infoContainer:: getMap()const
{
    this->map;
}
//>-------------------------------------------------------
vooid Q_role_infoContainer::load()
{
    int len = this->list->size();
    for( int i = 0; i < len; i++)
    {
        this->map.insert(std::pair<int, Q_role_infoBean*>(this->list[i]->name));
    }
}