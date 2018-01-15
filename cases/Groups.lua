local Comm = require "Comm"

local _M = {}

Comm.Group_Add(_M, require "cases/ws/group_en_word_score")
Comm.Group_Add(_M, require "cases/ws/group_en_sent_score")

return _M




