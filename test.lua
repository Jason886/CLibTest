_G.CaseStRun = 1
_G.CaseStSuc = 2
_G.CaseStFail = 3

LOG_I("hello")
LOG_W("hello")
LOG_E("hello")
LOG("hello")


function Sleep(n)
local t0 = os.clock()
  while os.clock() - t0 <= n do end
end


local cfg = [==[
{
    "appKey": "14255202120000cf",
    "secretKey": "988aaf63008b6db30f38bd60be0c3534",
    "provision": "data/aiengine.provision",
    "deviceId": "03d40274043505adbc06820700080009",
    "prof": {
        "enable": 1
    },
    "cloud": {
        "server": "ws://10.0.200.20:8090"
    }
}
]==]

local start = [==[
    {
        "coreProvideType": "cloud",
        "serialNumber": "db13-d6ef-16aa-c949-78af",
        "app": {
            "userId": "xxx"
        },
        "audio": {
            "audioType": "wav",
            "sampleRate": 16000,
            "channel": 1,
            "sampleBytes": 2,
            "saveAudio":{
                "saveType":"wav",
                "saveDir":"./audio"
            }
        },
        "request": {
            "coreType": "en.word.score",
            "rank": 5,
            "precision": 0.5,
            "refText": "hello"
        }
    }
]==]

local function _callback(a, b, c, d, e)
    print('!!!!!callback')
    print(a)
    print(b)
    print(c)
    print(d)
    print(e)
    return 0
end

local egn = aiengine_new(cfg);
local ret = aiengine_start(egn, start, nil, _callback, {})
print('ret = ' .. ret)

local file = File_Open("test.lua", "r", 1024)
File_Read(file)

aiengine_feed(egn, file.readBuf, file.nRead)
Sleep(1)
ret = aiengine_stop(egn)
print('!!!!!!!!!!ret = ' .. ret)
Sleep(20)
aiengine_delete(egn)
print('!!! deleteed')

do
    return
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













