#include <iostream>
#include <map>
#include "param_table.h"

using namespace std;


/* std::map<char* => class, std::map<char* => parameter_name, parameter>> map; */
std::map<char*, std::map<char*, parameter> > param_map;
std::map<char*, parameter> class_standard;

void config_standard(char* comment, char* value_type, char* default_value, char* xml_name, char* param_name){
  parameter tmp_parameter;

  tmp_parameter.comment = comment;
  tmp_parameter.value_type = value_type;
  tmp_parameter.default_value = default_value;
  tmp_parameter.xml_name = xml_name;

  class_standard[param_name] = tmp_parameter;
}

void init(){
  /* o map de cima vai ser uma class instanciada pelo init() inicial depois temos de fazer uma lista de parametros iniciais para colocar na class de standard e fazemos uma forma de iniciar a class para depois colocar no param_map */

  config_standard((char *)"", (char *)"", (char *)"", (char *)"", (char *)"challenge name");
  config_standard((char *)"", (char *)"", (char *)"", (char *)"", (char *)"challenge type");
  config_standard((char *)"", (char *)"uint", (char *)"50", (char *)"CycleTime", (char *)"cycle time");
  config_standard((char *)"", (char *)"uint", (char *)"2400", (char *)"SimTime", (char *)"duration");

  param_map[(char *)"class_standard"] = class_standard;
}

bool add_parameter(char* class_name, char* param_name, parameter param){
  if(exists(class_name)){
    if(exists(class_name, param_name)){
      throw PARAMETER_ALREADY_EXISTS;
    }

    std::map<char*, parameter> Class = find(class_name);
    Class[param_name] = param;
    /*
    Class.insert(param);
    */
  }else{
    std::map<char*, parameter> new_map;
    new_map[param_name] = param;
    param_map[class_name] = new_map;
    /*
    param_map.insert(pair<char*, std::map<char*, parameter> >(class_name, new_map));
    */
  }
  return true;
}

/*
  NOTA: Quando soubermos que o parâmetro existe, temos armazenado numa variavel e queremos saber se existe default value é mais eficiente fazer: param.default_value.length==0
*/
bool has_default_value(char* class_name, char* parameter_name){
  if(!exists(class_name, parameter_name)){
    throw PARAMETER_DOESNT_EXISTS;
  }

  parameter param = find(class_name, parameter_name);
  return true;
  /*
  if(param.default_value()==0){
    return false;
  }else{
    return true;
  }
  */
}

std::map<char*, parameter> find(char* class_name){
  if(!exists(class_name)){
    throw MAP_CLASS_DOESNT_EXISTS;
  }
  return param_map[class_name];
}

void print_parameter(char* class_name, char* parameter_name, parameter param){
  cout << "\""<< parameter_name << "\" : { \n " << "\t\"comment\" : \""<< param.comment << "\" \n" << "\t\"class\" : \""<< class_name << "\" \n" << "\t\"value type\" : \""<< param.value_type << "\" \n" << "\t\"default value\" : \""<< param.default_value << "\" \n"  << "\t\"XML name\" : \""<< param.xml_name << "\" \n" << "},"<< endl;
}

parameter find(char* class_name, char* parameter_name){
  if(!exists(class_name, parameter_name)){
  	throw PARAMETER_DOESNT_EXISTS;
  }
  return find(class_name)[parameter_name];
}

bool exists(char* class_name){
  return param_map.count(class_name)!=0;
}

bool exists(char* class_name, char* parameter_name){
  return exists(class_name) && find(class_name).count(parameter_name)!=0;
}

std::map<char*, std::map<char*, parameter> >::iterator it1;
std::map<char*, parameter>::iterator it2;

void print_symboltable(){
    
    for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        // itator->first = key
        // itator->second = value
        string key = it1->first;

        cout << "\n"<< key <<endl;


        for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
        {
          if(it2->second.default_value == NULL){
            string key2 = it2->first;
            string comment =it2->second.comment;
            string value_type  = it2->second.value_type;
            string xml_name = it2->second.xml_name;
            cout << "\n \t" << key2 <<endl;
            cout << "\n \t \t \"comment\": " << comment <<endl;
            cout << "\n \t \t \"value type\": " << value_type <<endl;
            cout << "\n \t \t \"xml name\": " << xml_name <<endl;
          }
          else{
            string key2 = it2->first;
            string comment =it2->second.comment;
            string value_type  = it2->second.value_type;
            string default_value = it2->second.default_value;
            string xml_name = it2->second.xml_name;
            cout << "\n \t" << key2 <<endl;
            cout << "\n \t \t \"comment\": " << comment <<endl;
            cout << "\n \t \t \"value type\": " << value_type <<endl;
            cout << "\n \t \t \"default value\": " << default_value <<endl;
            cout << "\n \t \t \"xml name\": " << xml_name <<endl;
          }

        }
          
      }
    
}

/*
int main (){
    parameter one;
    parameter two;
    char* key1 = (char *)"key time"; // param name
    char* key2 = (char *)"beacon sensor aperture";

    one.comment = (char *)"Time to finish an intermmediate goal";
    char* class_name_one = (char *)"scoring parameters";
    one.value_type = (char *)"uint";
    one.default_value = (char *)"2";
    one.xml_name = (char *)"KeyTime";

    two.comment = (char *)"Aperture of the beacon sensor";
    char* class_name_two = (char *)"robot modelling parameters";
    two.value_type = (char *)"double";
    two.default_value = (char *)"PI";
    two.xml_name = (char *)"BeaconAperture";

    add_parameter(class_name_one, key1, one);
    add_parameter(class_name_two, key2, two);

    print_symboltable();
}


*/