//================================================================================================================================================
//
// (c) GIE 29.03.2005
//
//================================================================================================================================================
// NAME: guid_map.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "guid_map.factory.h"
//================================================================================================================================================
#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.client.h"

#include <map>
//================================================================================================================================================
namespace gie_idl {

    typedef gie::ccom::list<guid_map_i> guid_map_interfaces_t;
    
    struct guid_map_impl_t
        : gie::ccom::c_object_root_t
          <
             guid_map_impl_t,           //self type
             guid_map_i ,               //unknown from this interface
             guid_map_interfaces_t,     //supported interfaces
             gie::ccom::counter_impl_t<>
          >
    {
        const guid_map_i_insert_result_t insert(const gie::ccom::guid_t& key, const boost::intrusive_ptr<gie::ccom::unknown_i>& unknown)
        {
            const insert_result_t& r = assoc_map_.insert( std::make_pair(key, unknown) );
            return guid_map_i_insert_result_t(r.first->second, r.second);
        }

        const boost::intrusive_ptr<gie::ccom::unknown_i> operator[](const gie::ccom::guid_t& key)const
        {
            const assoc_map_t::const_iterator& r = assoc_map_.find(key);
            if( r==assoc_map_.end() )
            {
                return boost::intrusive_ptr<gie::ccom::unknown_i>();
            }
            else
            {
                return r->second;
            }
        }

    private:
        typedef boost::intrusive_ptr<gie::ccom::unknown_i> value_t;
        typedef std::map<gie::ccom::guid_t, value_t> assoc_map_t;
        typedef std::pair<assoc_map_t::iterator, const bool> insert_result_t;

        assoc_map_t assoc_map_;
    };

    typedef gie::ccom::c_object_t<guid_map_impl_t> guid_map_c;


    guid_map_ptr_t create_guid_map()
    {
        return guid_map_ptr_t( guid_map_c::create<guid_map_i>(), false );
    }


}
//================================================================================================================================================
