_G.CaseStRun = 1
_G.CaseStSuc = 2
_G.CaseStFail = 3

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













