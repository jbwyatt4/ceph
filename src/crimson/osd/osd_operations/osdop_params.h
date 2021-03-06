#pragma once

#include "messages/MOSDOp.h"
#include "osd/osd_types.h"
#include "crimson/common/type_helpers.h"

// The fields in this struct are parameters that may be needed in multiple
// level of processing. I inclosed all those parameters in this struct to
// avoid passing each of them as a method parameter.
struct osd_op_params_t {
  Ref<MOSDOp> req;
  eversion_t at_version;
  eversion_t pg_trim_to;
  eversion_t min_last_complete_ondisk;
  eversion_t last_complete;
  version_t user_at_version;
  bool user_modify = false;

  osd_op_params_t(Ref<MOSDOp>&& req) : req(req) {}
  osd_op_params_t(Ref<MOSDOp>&& req, eversion_t at_version, eversion_t pg_trim_to,
      eversion_t mlcod, eversion_t lc, version_t user_at_version) :
    req(req), at_version(at_version), pg_trim_to(pg_trim_to),
    min_last_complete_ondisk(mlcod), last_complete(lc),
    user_at_version(user_at_version) {}
};
