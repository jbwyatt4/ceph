#ifndef __MOSDPGUPDATE_H
#define __MOSDPGUPDATE_H

#include "msg/Message.h"

class MOSDPGUpdate : public Message {
  version_t   map_version;
  pg_t        pgid;
  //pginfo_t    info;
  bool        complete;
  version_t   last_any_complete;

 public:
  version_t get_version() { return map_version; }
  pg_t get_pgid() { return pgid; }
  //pginfo_t& get_pginfo() { return info; }
  bool is_complete() { return complete; }
  version_t get_last_any_complete() { return last_any_complete; }

  MOSDPGUpdate() {}
  MOSDPGUpdate(version_t mv, pg_t pgid, bool complete, version_t last_any_complete) :
	Message(MSG_OSD_PG_UPDATE) {
	this->map_version = mv;
	this->pgid = pgid;
	this->complete = complete;
	this->last_any_complete = last_any_complete;
  }
  
  char *get_type_name() { return "PGUp"; }

  void encode_payload() {
	payload.append((char*)&map_version, sizeof(map_version));
	payload.append((char*)&pgid, sizeof(pgid));
	payload.append((char*)&complete, sizeof(complete));
	payload.append((char*)&last_any_complete, sizeof(last_any_complete));
  }
  void decode_payload() {
	int off = 0;
	payload.copy(off, sizeof(map_version), (char*)&map_version);
	off += sizeof(map_version);
	payload.copy(off, sizeof(pgid), (char*)&pgid);
	off += sizeof(pgid);
	payload.copy(off, sizeof(complete), (char*)&complete);
	off += sizeof(complete);
	payload.copy(off, sizeof(last_any_complete), (char*)&last_any_complete);
	off += sizeof(last_any_complete);
  }
};

#endif
