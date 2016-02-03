#ifndef SM_BOOST_PROPERTY_TREE_HPP
#define SM_BOOST_PROPERTY_TREE_HPP

#include "PropertyTree.hpp"

#ifdef toupper
#undef toupper
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem/path.hpp>
#include <typeinfo>
#include <sm/BoostPropertyTreeSupport.hpp>

namespace sm {
  
  class BoostPropertyTree : public PropertyTree
  {
  public:
    typedef boost::property_tree::ptree ptree;
    typedef ptree::iterator iterator;
    typedef ptree::const_iterator const_iterator;
    

    BoostPropertyTree(const std::string & baseNamespace = "");
    BoostPropertyTree(const boost::property_tree::ptree& ptree, const std::string & baseNamespace = "");
    virtual ~BoostPropertyTree();

    void loadXml(const boost::filesystem::path & fileName);
    void loadXmlFromString(const std::string & xml);
    void saveXml(const boost::filesystem::path & fileName) const;
 
    void loadIni(const boost::filesystem::path & fileName);
    void saveIni(const boost::filesystem::path & fileName) const;

    void loadInfo(const boost::filesystem::path & fileName);
    void saveInfo(const boost::filesystem::path & fileName) const;

    void loadXmlStr(const std::string & fileName){loadXml(fileName);}
    void saveXmlStr(const std::string & fileName) const{saveXml(fileName);}

    void loadIniStr(const std::string & fileName){loadIni(fileName);}
    void saveIniStr(const std::string & fileName) const{saveIni(fileName);}

    void loadInfoStr(const std::string & fileName){loadInfo(fileName);}
    void saveInfoStr(const std::string & fileName) const{saveInfo(fileName);}

    std::string asInfoString() const;
    
    /**
     * Update this ptree with another, allowing merging of ptrees
     * @param with the other ptree
     * @param createIfNecessary if true all necessary entries will be created automatically
     *                          otherwise a KeyNotFoundException if there is no such key already
     * @param ignoreEmptyUpdates all values in \p with that are empty or whitespace only will be ignored
     */
    void update(const BoostPropertyTree & with, bool createIfNecessary, bool ignoreEmptyUpdates);
    void update(const BoostPropertyTree & with, bool createIfNecessary){ update(with, createIfNecessary, false); }
    void update(const BoostPropertyTree & with){ update(with, true); }

    iterator begin() ;
    const_iterator begin() const;
    iterator end() ;
    const_iterator end() const;    

    static bool isHumanReadableInputOutput() {
      return humanReadableInputOutput;
    }

    static void setHumanReadableInputOutput(bool humanReadableInputOutput) {
      BoostPropertyTree::humanReadableInputOutput = humanReadableInputOutput;
    }
  private:
    // It is important that this implementation have no members.

    static bool humanReadableInputOutput;
  };


} // namespace sm


#endif /* SM_BOOST_PROPERTY_TREE_IMPLEMENTATION_HPP */
