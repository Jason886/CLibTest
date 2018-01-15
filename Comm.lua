local _M = {}

local function _Obj_Copy(obj)
	if type(obj) ~= 'table' then return nil end
	local copy = {}

	for k, v in pairs(obj) do
		if type(v) ~= "table" then
			copy[k] = v
		else
			copy[k] = _Obj_Copy(copy)
		end
	end
	return copy
end


local function _Case_Add(cases, case_cfg)
	if type(cases) ~= 'table' then return end
	if type(case_cfg) ~= 'table' then return end

	for i, v in ipairs(case_cfg) do
		table.insert(cases, v)

		if v.copyTimes and v.copyTimes > 0 then

			local copyTimes = 0
			while (copyTimes < v.copyTimes) do
				local copyed = _Obj_Copy(v)
				copyed.copyIndex = copyTimes + 1
				table.insert(cases, copyed)
				copyTimes = copyTimes + 1
			end
		end
	end
end


local function _Group_Copy(group)
	if type(group) ~= 'table' then return nil end
	local copyed = {}

	for k, v in pairs(group) do
		if type(v) == "table" then

			if k ~= "cases" then
				copyed[k] = _Obj_Copy(v)
			else
				copyed.cases = {}
				for caseI, caseV in ipairs(v) do
					--print('caseV' .. caseV)
					if caseV ~= "" then
						local case_cfg = require(caseV)
						_Case_Add(copyed.cases, case_cfg)
					end
				end
			end
		else
			if k ~= "copyTimes" then
				copyed[k] = v
			end
		end
	end

	return copyed
end


function _M.Group_Add(groups, group_cfg)
	if type(groups) ~= 'table' then return end
	if type(group_cfg) ~= 'table' then return end

	for i, v in ipairs(group_cfg) do
		local group = _Group_Copy(v)
		group.copyTimes = v.copyTimes
		table.insert(groups, group)

		if v.copyTimes and v.copyTimes > 0 then

			local copyTimes = 0
			while (copyTimes < v.copyTimes) do
				local copyed = _Group_Copy(v)
				copyed.copyIndex = copyTimes + 1
				table.insert(groups, copyed)
				copyTimes = copyTimes + 1
			end
		end
	end
end

return _M
