#pragma once

#include "session.h"

#include <optional>
#include <string>

class SessionStorage
{
public:
  virtual ~SessionStorage() = default;

  virtual bool save(const SessionRecord &session) = 0;
  virtual std::optional<SessionRecord> load(const std::string &session_id) = 0;
  virtual bool remove(const std::string &session_id) = 0;
  virtual void cleanup_expired(std::int64_t now_epoch) = 0;
};
