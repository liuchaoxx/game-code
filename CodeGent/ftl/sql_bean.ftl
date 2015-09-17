#ifndef _${name?upper_case}_H
#define _${name?upper_case}_H
<#assign ustring = false uvector = false/> <#list fields as field > <#if field.ptype = "string"> <#assign ustring = true/> </#if> </#list>
#include <vector>
#include <map>
<#if ustring = true>
#include <iostream>
#include <string>

using std::string;
</#if>
using std::vector;
using std::map;

//>=======================================================
/*
* classname   ${name?cap_first}Bean
* description  ${describe}
**/
class ${name?cap_first}Bean
{    
public:
    <#list fields as field >
    /*
    * description  get ${field.describe}
    **/
    ${field.ptype} get${field.name?cap_first}() const
    //
    /*
    * description  set ${field.describe}
    **/
    void set${field.name?cap_first}(${field.ptype} _${field.name})
    </#list>   
private:
    <#list fields as field >
    ${field.ptype} ${field.name};
    </#list>
};

<#list fields as field >
//>-------------------------------------------------------
//description  get ${field.describe}
${field.ptype} ${name?cap_first}Bean:: get${field.name?cap_first}() const
{
    return this->${field.name};
}

//>-------------------------------------------------------
//description  set ${field.describe}
void ${name?cap_first}Bean:: set${field.name?cap_first}(${field.ptype} _${field.name})
{
    this->${field.name} = _${field.name};
}

</#list>    

//>=======================================================
/*
* classname   ${name?cap_first}Container
* description  ${describe}
**/
class ${name?cap_first}Dao : public BaseDao
{
public:
    ${name?cap_first}Dao();
    vector<${name?cap_first}Bean*>* select();
private:
    SqlSessionFactory *factory_;
};

${name?cap_first}Dao : ${name?cap_first}Dao()
{
    factory = getFactory();
}

vector<${name?cap_first}Bean*>* ${name?cap_first}Dao::select()
{
    vector<${name?cap_first}Bean*> *list = NULL;
    SqlSession *session = this->factory_->openSession();
    list = session->selectList<${name?cap_first}>("${name}.select");
    session->close();
    return list;
}

//>=======================================================
/*
* classname   ${name?cap_first}Container
* description  ${describe}
**/
class ${name?cap_first}Container
{    
public:
    ${name?cap_first}Container();
    const vector<${name?cap_first}Bean*>& getList()const;
    <#list fields as field >
    <#if field.ctype = "1">
    const map<<${field.ptype}, ${name?cap_first}Bean*>& getMap()const
    </#if> 
    </#list>   
    void load();
private:
    vector<${name?cap_first}Bean*> *list;
    <#list fields as field >
    <#if field.ctype = "1">
    map<<${field.ptype}, ${name?cap_first}Bean*> map;
    </#if> 
    </#list> 
    ${name?cap_first}Dao *dao;
};

//>-------------------------------------------------------          
${name?cap_first}Container:${name?cap_first}Container()
{
    this->list = NULL;
    this->dao = new ${name?cap_first}Dao();
}

//>-------------------------------------------------------
//description  getList
const vector<${name?cap_first}Bean*>& ${name?cap_first}Container:: getList()const;
{
    return this->list;
}

//>-------------------------------------------------------
<#list fields as field >
<#if field.ctype = "1">
//description  set ${field.describe}
const map<${field.ptype}, ${name?cap_first}Bean*>& ${name?cap_first}Container:: getMap()const
{
    this->map;
}
</#if>
</#list>  
//>-------------------------------------------------------
vooid ${name?cap_first}Container::load()
{
    int len = this->list->size();
    for( int i = 0; i < len; i++)
    {
        <#list fields as field >
        <#if field.ctype = "1">
        this->map.insert(std::pair<${field.ptype}, ${name?cap_first}Bean*>(this->list[i]->name));
        </#if>
        </#list>  
    }
}