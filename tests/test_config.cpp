#include "../sylar/config.h"
#include "../sylar/log.h"
#include "../sylar/util.h"
#include <vector>

//遍历yaml
void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    } else if(node.IsNull()) {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()) {
        for(auto it = node.begin();
                it != node.end(); ++it) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
                    << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
                << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}    
sylar::ConfigVar<int>::ptr g_int_value_congif = sylar::Config::Lookup("system.port", (int)8080, "system port");
sylar::ConfigVar<float>::ptr g_float_value_congif = sylar::Config::Lookup("system.value", (float)10.2, "system value");
sylar::ConfigVar<std::vector<int>>::ptr g_int_vec_value_config = sylar::Config::Lookup("system.int_vec", std::vector<int>{1,2}, "system int vec");
sylar::ConfigVar<std::list<int>>::ptr g_int_list_value_config = sylar::Config::Lookup("system.int_list", std::list<int>{1,2}, "system int vec");
sylar::ConfigVar<std::set<int>>::ptr g_int_set_value_config = sylar::Config::Lookup("system.int_set", std::set<int>{1,2}, "system int vec");
sylar::ConfigVar<std::map<std::string, int>>::ptr g_str_int_map_value_config = sylar::Config::Lookup("system.str_int_map", std::map<std::string,int>{{"k",2}}, "system str int map");

void test_yaml() {

    YAML::Node root = YAML::LoadFile("/home/zyy/workspace/sylar/bin/conf/log.yml");
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root ;
    print_yaml(root,0);
}

void test_config() {
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before" << g_int_value_congif->toString();
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before" <<g_float_value_congif->toString();
#define XX(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for(auto&i : v) { \
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name  ":" << i; \
        } \
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name  "yaml: " <<g_var->toString(); \
    }

#define XX_M(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for(auto&i : v) { \
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name  ": {" \
            <<i.first << " - " << i.second << "}"; \
        } \
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name  "yaml: " <<g_var->toString(); \
    }

    XX(g_int_list_value_config, int_list, before);
    XX(g_int_vec_value_config, int_vec, before);
    XX(g_int_set_value_config, int_set, before);
    XX_M(g_str_int_map_value_config, int_set, before);

    YAML::Node root = YAML::LoadFile("/home/zyy/workspace/sylar/bin/conf/log.yml");
    sylar::Config::LoadFromYaml(root); 

    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after" << g_int_value_congif->getValue();
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after" <<g_float_value_congif->getValue();

    XX(g_int_list_value_config, int_list, after);
    XX(g_int_vec_value_config, int_vec, after);
    XX(g_int_set_value_config, int_set, after);
    XX_M(g_str_int_map_value_config, int_set, after);
}

class Person {
public:
    Person() {};
    std::string m_name;
    int m_age = 0;
    bool m_sex = 0;

    std::string toString() const {
        std::stringstream ss;
        ss << "[Person name=" << m_name
           << " age=" << m_age
           << " sex=" << m_sex
           << "]"; 
        return ss.str();
    }

    bool operator==(const Person& oth) const {
        return m_name == oth.m_name
            && m_age == oth.m_age
            && m_sex == oth.m_sex;
    }
};

namespace sylar {

template<>
class LexicalCast<std::string, Person> {
public:
    Person operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};

template<>
class LexicalCast<Person, std::string> {
public:
    std::string operator()(const Person& p) {
        YAML::Node node;
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};
}

sylar::ConfigVar<Person>::ptr g_person =
    sylar::Config::Lookup("class.person", Person(), "system person");
sylar::ConfigVar<std::map<std::string, Person> >::ptr g_person_map =
    sylar::Config::Lookup("class.map", std::map<std::string, Person>(), "system person");
sylar::ConfigVar<std::map<std::string, std::vector<Person> > >::ptr g_person_vec_map =
    sylar::Config::Lookup("class.vec_map", std::map<std::string, std::vector<Person> >(), "system person");

void test_class() {

#define XX_PM(g_var, prefix) \
{ \
    auto m = g_person_map->getValue(); \
    for(auto& i : m) { \
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) <<  prefix << ": " << i.first << " - " << i.second.toString(); \
    } \
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) <<  prefix << ": size=" << m.size(); \
}
    
    // XX_PM(g_person_map,"class.map before");
    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_person->getValue().toString() << "-" <<g_person->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_person_vec_map->toString();

    YAML::Node root = YAML::LoadFile("/home/zyy/workspace/sylar/bin/conf/log.yml");
    sylar::Config::LoadFromYaml(root);

    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_person->getValue().toString() << "-" <<g_person->toString();
    // XX_PM(g_person_map,"class.map after");
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_person_vec_map->toString();

}


int main (int argc, char** argv) {

    test_class();
    return 0;
}