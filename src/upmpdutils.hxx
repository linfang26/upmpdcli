/* Copyright (C) 2014 J.F.Dockes
 *	 This program is free software; you can redistribute it and/or modify
 *	 it under the terms of the GNU General Public License as published by
 *	 the Free Software Foundation; either version 2 of the License, or
 *	 (at your option) any later version.
 *
 *	 This program is distributed in the hope that it will be useful,
 *	 but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	 GNU General Public License for more details.
 *
 *	 You should have received a copy of the GNU General Public License
 *	 along with this program; if not, write to the
 *	 Free Software Foundation, Inc.,
 *	 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#ifndef _UPMPDUTILS_H_X_INCLUDED_
#define _UPMPDUTILS_H_X_INCLUDED_

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "libupnpp/control/cdircontent.hxx"

class UpSong;

// Convert between db value to percent values (Get/Set Volume and VolumeDb)
extern int percentodbvalue(int value);
extern int dbvaluetopercent(int dbvalue);

extern bool sleepms(int ms);

// Return mapvalue or null strings, for maps where absent entry and
// null data are equivalent
extern const std::string& mapget(
    const std::unordered_map<std::string, std::string>& im, 
    const std::string& k);

// Format a didl fragment from MPD status data
extern std::string didlmake(const UpSong& song);

// Convert UPnP metadata to UpSong for mpdcli to use
extern bool uMetaToUpSong(const std::string&, UpSong *ups);
// Convert UPnP content directory entry object to UpSong
bool dirObjToUpSong(const UPnPClient::UPnPDirObject& dobj, UpSong *ups);

// Extract the set of formats from protocolinfo data (comma separated
// list of 'proto:net:format:extradata' elements, e.g. http-get:*:audio/mpeg:*) 
// All format strings are changed to lower case in the output set.
extern bool protocolInfoToFormats(const std::string& pinfo,
                                  std::unordered_set<std::string>& formats);

// Extract content format from resource protocolinfo attribute. This
// should be made an UPnPResource method one day
std::string resourceContentFormat(const UPnPClient::UPnPResource& res);


// Replace the first occurrence of regexp. cxx11 regex does not work
// that well yet...
extern std::string regsub1(const std::string& sexp, const std::string& input, 
                           const std::string& repl);

// Return map with "newer" elements which differ from "old".  Old may
// have fewer elts than "newer" (e.g. may be empty), we use the
// "newer" entries for diffing. This is used to compute state changes.
extern std::unordered_map<std::string, std::string> 
diffmaps(const std::unordered_map<std::string, std::string>& old,
         const std::unordered_map<std::string, std::string>& newer);

#endif /* _UPMPDUTILS_H_X_INCLUDED_ */
