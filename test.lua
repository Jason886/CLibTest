_G.CaseStRun = 1
_G.CaseStSuc = 2
_G.CaseStFail = 3


LOG_I("hello")
LOG_W("hello")
LOG_E("hello")
LOG("hello")

local f = File_Open("test.lua", "r", 1024)
File_Read(f, 512);
print(f.nRead)
if f.nRead > 0 then
    
end

local Groups = require "cases/Groups"

for i, v in ipairs(Groups) do
	if v.run then
		local ret = v:run()
		if 0 ~= ret then
			break
		end
	end
end


-- 统计运行结果













