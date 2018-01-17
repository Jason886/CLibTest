local _M = {}

function _M.Group_Run(group)
    local rc = 0
    local input = group.input
    local runCtx = {}
    group.runCtx = runCtx

    local groupCopyName = group.copyIndex and ('(copy' .. group.copyIndex .. ')') or ''
    print('[Group ' .. group.name .. groupCopyName .. ' Start]')

    runCtx.egn = aiengine_new(input.cfg)
    if runCtx.egn == nil then
        rc = -1
        goto ret
    end

    for i, v in ipairs(group.cases) do
        if v.run then
            local case_rc = v:run(group)
            if case_rc ~= 0 then
                rc = -1
                goto ret
            end
        end
    end

::ret::

    if runCtx.egn ~= nil then
        aiengine_delete(runCtx.egn)
        runCtx.egn = nil
    end

    if rc ~= 0 then
        print('[Group ' .. group.name .. groupCopyName .. ' Failure]')
    else
        print('[Group ' .. group.name .. groupCopyName .. ' Finish]')
    end
    return rc
end

function _M.Case_Run(case, group)
    local rc = 0
    local runCtx = group.runCtx
    local input = case.input
    local egn_rc = 0
    local nRead = 0
    local file = nil

    local groupCopyName = group.copyIndex and ('(copy' .. group.copyIndex .. ')') or ''
    local caseCopyName = case.copyIndex and ('(copy' .. case.copyIndex .. ')') or ''
    print('[Case ' .. group.name ..groupCopyName .. '.' .. case.name ..caseCopyName .. ' Start]')

    file = File_Open(input.audio_file, "r", 4096)
    if not file then
        rc = -1
        goto ret
    end

    egn_rc = aiengine_start(runCtx.egn, input.param, nil, case.check, case)
    if egn_rc ~= 0 then
        aiengine_stop(runCtx.egn)
        rc = -1
        goto ret
    end

    nRead = File_Read(file)
    while  nRead and nRead > 0 do
        aiengine_feed(runCtx.egn, file.readBuf, file.nRead)
        nRead = File_Read(file)
    end

    File_Close(file)

    aiengine_stop(runCtx.egn)

    SleepMs(10000)  -- 等待结果

::ret::
    if rc ~= 0 then
        print('[Case ' .. group.name .. groupCopyName .. '.' .. case.name ..caseCopyName .. ' Failure]')
    else
        print('[Case ' .. group.name .. groupCopyName .. '.' .. case.name ..caseCopyName .. ' Finish]')
    end
    return rc
end


return _M
