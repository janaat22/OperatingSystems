# Python code obfuscated by www.development-tools.net 
 

import base64, codecs
magic = 'IyEgL3Vzci9iaW4vcHl0aG9uMwoiIiIgIEEgbGVzcyBib2d1cyBzb2x1dGlvbiBvZiBGYWxsIDIwMjAgZmlyc3QgYXNzaWdubWVudC4KICAgICBJdCB1c2VzIG9zLmZvcmsoKSBhbmQgb3MuZXhlY3ZwKCkgaW5zdGVhZCBvZiBvcy5zeXN0ZW0oKQogICAgIGJ1dCBpcyBzdGlsbCBpbiBQeXRob24zLgogICAgIGh0dHBzOi8vd3d3LnB5dGhvbi1jb3Vyc2UuZXUvZm9ya2luZy5waHAKICAgICBpcyBhIGdyZWF0IHJlZmVyZW56LgogICAgIEouLUYuIFBhcmlzCiAgICAgT2N0b2JlciAyLCAyMDIwCiIiIgppbXBvcnQgb3MsIHN5cwoKZGVmIGNoYW5nZURpcmVjdG9yeShhcmdjLCBhcmd2KSA6CiAgICBpZiBhcmdjID09ICAyIDoKICAgICAgICBvcy5jaGRpcihhcmd2WzFdKQogICAgZWxpZiBhcmdjID09IDEgOgogICAgICAgIG9zLmNoZGlyKG9zLmVudmlyb25bJ0hPTUUnXSkKICAgIGVsc2UgOgogICAgICAgIHByaW50KCJOb3RTb0Zha2VTaGVsbDogY2Q6IHRvbyBtYW55IGFyZ3VtZW50cyIpCgpkZWYgbmV3UGF0aChhcmdjLCBhcmd2KSA6CiAgICBpZiBhcmdjID09ICAyIDoKICAgICAgICBvcy5wdXRlbnYoJ1BBVEgnLCBhcmd2WzFdKSAjIEluIEMgaXQgd291bGQgYmUgcHV0ZW52KCJQQVRIPW5ld3BhdGgiKTsKICAgIGVsaWYgYXJnYyA9PSAxIDoKICAgICAgICBwcmludCgiTm90U29GYWtlU2hlbGw6IG5ld3BhdGg6IG5vIGFyZ3VtZ'
love = 'J50plVcPvNtVPOyoUAyVQbXVPNtVPNtVPOjpzyhqPtvGz90H29TLJgyH2uyoTj6VT5yq3OuqTt6VUEiolOgLJ55VTSlM3IgMJ50plVcPtcxMJLtpzIRnKWyL3DbLKWaLljtLKWaqvxtBtbtVPNtVlOjpzyhqPuupzq2XDbtVPNtnJLtW2yhqT8aVT5iqPOcovOupzq2VQbXVPNtVPNtVPOjpzyhqPtvGz90H29TLJgyH2uyoTj6VUWyMTylMJA0BvOgnKAmnJ5aVTyhqT8vXDbtVPNtMJkcMvOupzq2JmSqVQ09VPqcoaEiWlOipvOupzq2Jl0kKFN9CFNanJ50olp6PvNtVPNtVPNtpUWcoaDbVx5iqSAiEzSeMIAbMJkfBvOlMJEcpzIwqQbtoJympTkuL2IxVTyhqT8vXDbtVPNtMJkmMFN6PvNtVPNtVPNtVlOmpTkcqPOupzq2VTyhqT8tpUWiMUIwMKVtpUWiMTSlM3LtLJ5xVTAioaA1oJIlVTAioaAupzq2PvNtVPNtVPNtVlOgqKA0VTSfp28tpzIgo3MyVTSlM3MoZS0tMaWioFOjpz9xLKWaqvOuozDtLJExVUEiVTy0VTRtqUWunJkcozptoaIfoPNXVPNtVPNtVPOvpzIun3OinJ50VQ0tLKWaqv5cozEyrPtanJ50olpcPvNtVPNtVPNtpUWiMTSlM3LtCFOupzq2JmR6LaWyLJgjo2yhqS0XVPNtVPNtVPOwo25mLKWaqvN9VTSlM3MoLaWyLJgjo2yhqPfkBy0XVPNtVPNtVPNwVUOlnJ50XUOlo2Eupzq2XDbtVPNtVPNtVPZtpUWcoaDbL29hp2SlM3LcPvNtVPNtVPNtn2yxpTyxVQ0to3ZhMz9lnltcPvNtVPNtVPNtnJLtn2yxpTyxVQ09VQNtBvNwVTAbnJ'
god = 'xkIHByb2Nlc3MgYW5kIGZ1dHVyZSBjb25zdW1lcgogICAgICAgICAgICBzdGRpbiAgPSBzeXMuc3RkaW4uZmlsZW5vKCkKICAgICAgICAgICAgc3Rkb3V0ID0gc3lzLnN0ZG91dC5maWxlbm8oKQogICAgICAgICAgICBjb25zSW4sIHByb2RPdXQgPSBvcy5waXBlKCkKICAgICAgICAgICAgZ3JhbmRraWRwaWQgPSBvcy5mb3JrKCkKICAgICAgICAgICAgaWYgZ3JhbmRraWRwaWQgPT0gMCA6ICMgcHJvZHVjZXIgcHJvY2VzcwogICAgICAgICAgICAgICAgb3MuZHVwMihwcm9kT3V0LCBzdGRvdXQpCiAgICAgICAgICAgICAgICBvcy5jbG9zZShjb25zSW4pCiAgICAgICAgICAgICAgICBvcy5jbG9zZShwcm9kT3V0KQogICAgICAgICAgICAgICAgb3MuZXhlY3ZwKHByb2Rhcmd2WzBdLCBwcm9kYXJndikKICAgICAgICAgICAgICAgIHByaW50KCJQQU5JQzogZXhlY3ZwKCkgZmFpbGVkIikgCiAgICAgICAgICAgIGVsc2UgOiAgIyBjaGlsZCBwcm9jZXNzIGJlY29tZXMgdGhlIGNvbnN1bWVyCiAgICAgICAgICAgICAgICBvcy5kdXAyKGNvbnNJbiwgc3RkaW4pCiAgICAgICAgICAgICAgICBvcy5jbG9zZShjb25zSW4pCiAgICAgICAgICAgICAgICBvcy5jbG9zZShwcm9kT3V0KQogICAgICAgICAgICAgICAgb3MuZXhlY3ZwKGNvbnNhcmd2WzBdLCBjb25zYXJndikKICAgICAgICAgICAgICAgIHByaW50KCJQQU5JQzogZXhlY3ZwKCkgZmF'
destiny = 'coTIxVvxtPvNtVPNtVPNtMJkmMFN6PvNtVPNtVPNtVPNtVT9mYaqunKDbXDbXMTIzVUMuozyfoTSQLKAyXTSlM2ZfVTSlM3LcVQbXVPNtVTgcMUOcMPN9VT9mYzMipzfbXDbtVPNtnJLtn2yxpTyxVQ09VQNtBtbtVPNtVPNtVT9mYzI4MJA2pPuupzq2JmOqYPOupzq2XDbtVPNtVPNtVUOlnJ50XPWDDH5WDmbtMKuyL3MjXPxtMzScoTIxVvxtPvNtVPOyoUAyVQbXVPNtVPNtVPOipl53LJy0XPxXPaqbnJkyVPtkXFN6PvNtVPOupzqfnJ5yVQ0tnJ5jqKDbVx5iqSAiEzSeMIAbMJkfBvNvXDbtVPNtLKWaoTyhMF5mqUWcpPtcPvNtVPOupzq2VQ0tLKWaoTyhMF5mpTkcqPtcVPZtp3OuL2HtnKZtqTuyVUAioTHtpzIkqJylMJDtp2IjLKWuqT9lPvNtVPOupzqwVQ0toTIhXTSlM3LcPvNtVPOcMvOupzq2JmOqVQ09VPqyrTy0WlN6VlOSrTy0nJ5aVR5iqSAiEzSeMIAbMJkfPvNtVPNtVPNtMKucqPtcPvNtVPOyoTyzVTSlM3MoZS0tCG0tW25yq3OuqTtaVQbXVPNtVPNtVPOhMKqDLKEbXTSlM2ZfVTSlM3LcPvNtVPOyoTyzVTSlM3MoZS0tCG0tW2AxWmbXVPNtVPNtVPOwnTShM2IRnKWyL3EipaxbLKWaLljtLKWaqvxXVPNtVTIfnJLtLKWaqyfjKFN9CFNapzIxnKWyL3DaVQbtVlOVLJ5xoTyhMlOlMJEcpzIwqTyiotbtVPNtVPNtVUWyETylMJA0XTSlM2ZfVTSlM3LcPvNtVPOyoUAyVQbXVPNtVPNtVPO2LJ5coTkuD2SmMFuupzqwYPOupzq2XDb='
joy = '\x72\x6f\x74\x31\x33'
trust = eval('\x6d\x61\x67\x69\x63') + eval('\x63\x6f\x64\x65\x63\x73\x2e\x64\x65\x63\x6f\x64\x65\x28\x6c\x6f\x76\x65\x2c\x20\x6a\x6f\x79\x29') + eval('\x67\x6f\x64') + eval('\x63\x6f\x64\x65\x63\x73\x2e\x64\x65\x63\x6f\x64\x65\x28\x64\x65\x73\x74\x69\x6e\x79\x2c\x20\x6a\x6f\x79\x29')
eval(compile(base64.b64decode(eval('\x74\x72\x75\x73\x74')),'<string>','exec'))