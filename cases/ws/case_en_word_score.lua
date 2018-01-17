local CaseComm = require 'cases/CaseComm'

local function _check_case_001()
    LOG_I('!!!!!!!!!! case 1111 callback')
    LOG_I('!!!!!!!!!! case 1111 callback')
    LOG_I('!!!!!!!!!! case 1111 callback')
    LOG_I('!!!!!!!!!! case 1111 callback')
    SleepMs(1000)
end

return {
    {
        name = "001",
        input = {
            audio_file = "data/hello.wav",
            param = [==[
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
            ]==],

        },
        run = CaseComm.Case_Run,
        check = _check_case_001,
    },
}
