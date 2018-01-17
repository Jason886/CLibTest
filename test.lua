_G.CaseStRun = 1
_G.CaseStSuc = 2
_G.CaseStFail = 3

local Groups = require "cases/Groups"

for i, v in ipairs(Groups) do
    if v.run then
        local rc = v:run()
        if rc ~= 0 then
            break
        end
    end
end


-- 统计运行结果













