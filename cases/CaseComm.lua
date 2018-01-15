local _M = {}

function _M.Group_Run(group)
        local input = group.input
        local runCtx = {}
        group.runCtx = runCtx

        local groupCopyName = group.copyIndex and ('(copy' .. group.copyIndex .. ')') or ''

        -- print('[Group ' .. group.name .. groupCopyName .. ' Start]')


        --[[

        runCtx.egn = aiengine_new(input.cfg)
        if not runCtx.egn then
                return -1
        end
        --]]

        for i, v in ipairs(group.cases) do
                if v.run then
                        local ret = v:run(group)
                        if 0 ~= ret then
                                return -1
                        end
                end
        end

        --[[

        while (true) do
                local allDone = true
                for i, v in ipairs(group.cases) do
                        if not v.state or
                                (v.state ~= _G.CaseStSuc and v.state ~= _G.CaseStFail) then
                                allDone = false
                                break
                        end
                end
                if allDone then
                        break
                end
        end

        aiengine_delete(runCtx.egn)
        return 0
        ]]

        -- print('[Group ' .. group.name .. groupCopyName .. ' End]')
        return 0
end

function _M.Case_Run(case, group)
        local runCtx = group.runCtx
        local input = case.input

        local groupCopyName = group.copyIndex and ('(copy' .. group.copyIndex .. ')') or ''
        local caseCopyName = case.copyIndex and ('(copy' .. case.copyIndex .. ')') or ''

        print('[Case ' .. group.name ..groupCopyName .. '.' .. case.name ..caseCopyName .. ' Start]')


        print('[Case ' .. group.name .. groupCopyName .. '.' .. case.name ..caseCopyName .. ' End]')
        return 0
end


return _M