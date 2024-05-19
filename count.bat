for /R "%CD%" %f in (*) do @echo %~nxf: & find /v /c "" "%f"
