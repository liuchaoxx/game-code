#ifndef _${name?upper_case}_H
#define _${name?upper_case}_H
<#assign ustring = false uvector = false/> <#list fields as field > <#if field.ftype = "list"> <#assign uvector = true/> </#if> <#if field.ptype = "string"> <#assign ustring = true/> </#if> </#list>
#include "bean.h"
<#if ustring = true || uvector = true>
#include <iostream>
</#if>
<#if ustring = true>
#include <string>
</#if>
<#if uvector = true>
#include <vector>
</#if>

<#if ustring = true || uvector = true>
using namespace std;
</#if>

//classname   ${name}  
//description  ${describe}
class ${name} : public Bean
{    
public:
    //description data write to session
    virtual bool Write ( ISession& session );
    //description data read to session
    virtual bool Read ( ISession& session );
    <#list fields as field >
    //description  get ${field.describe}
    <#if field.ftype = "list">
    const vector<field.ptype>& Get${field.name?cap_first}() const
    <#else>
    ${field.ptype} Get${field.name?cap_first}() const
    </#if>
    //description  set ${field.describe}
    <#if field.ftype = "list">
    void Set${field.name?cap_first}(const vector<field.ptype>& _${field.name})
    <#else>
    void Set${field.name?cap_first}(${field.ptype} _${field.name})
    </#if>
    </#list>   
private:
    <#list fields as field >
    <#if field.ftype = "list">
    vector<field.ptype>  ${field.name};
    <#else>
    ${field.ptype} ${field.name};
    </#if>
    </#list>
};

//>-------------------------------------------------------
//description data write to session
bool ${name}:: Write ( ISession& session )
{
    <#list fields as field >
    <#if field.ftype = "list">
    int len = ${field.name}.size();
    WriteChar ( session, ( CHAR* )&len, sizeof(int) );
    for(int i = 0; i < len; i++)
    {
        <#if field.ctype = "class">
        Writebean(session, this->${field.name}[i]);
        <#elseif field.ptype = "string">
        WriteString ( session, this->${field.name}[i] );
        <#else>
        WriteChar ( session, ( CHAR* )&${field.name}[i], sizeof(${field.ptype}) );
        </#if>
    }
    <#elseif field.ptype = "string">
    WriteString ( session, this->${field.name} );
    <#else>
    WriteChar ( session, ( CHAR* )&${field.name}, sizeof( ${field.ptype} ) );
    </#if>
    </#list>
    return true;
}

//>-------------------------------------------------------
//description data read to session
bool ${name}:: Read ( ISession& session )
{
    <#list fields as field >
    <#if field.ftype = "list">
    int len = 0;
    this.ReadChar(session, ( CHAR* )&len, sizeof(int);
    for(int i = 0; i < len; i++)
    {
        <#if field.ctype = "class">
        ${field.ptype} bean;
        Readbean(session, bean);
        this.${field.name}.push_back(bean);
        <#elseif field.ptype = "string">
        string string;
        ReadString ( session, string );
        this.${field.name}.push_back(string);
        <#else>
        ${field.ptype} param;
        ReadChar ( session, ( CHAR* )&param, sizeof( ${field.ptype} ) );
         this.${field.name}.push_back(param);
        </#if>
    }
    <#elseif field.ptype = "string">
    ReadString ( session, this->${field.name} );
    <#else>
    ReadChar ( session, ( CHAR* )&${field.name}, sizeof( ${field.ptype} ) );
    </#if>
    </#list>
    return true;
}

<#list fields as field >
//>-------------------------------------------------------
//description  get ${field.describe}
<#if field.ftype = "list">
const vector<field.ptype>& ${name}:: Get${field.name?cap_first}() const
<#else>
${field.ptype} ${name}:: Get${field.name?cap_first}() const
</#if>
{
    return this.${field.name};
}

//>-------------------------------------------------------
//description  set ${field.describe}
<#if field.ftype = "list">
void ${name}:: Set${field.name?cap_first}(const vector<field.ptype>& _${field.name})
<#else>
void ${name}:: Set${field.name?cap_first}(${field.ptype} _${field.name})
</#if>
{
    this.${field.name} = _${field.name};
}

</#list>    