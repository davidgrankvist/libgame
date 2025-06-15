$currentScriptPath = $MyInvocation.MyCommand.Path
$repoPath = (Resolve-Path (Join-Path (Split-Path -Parent $currentScriptPath) "..")).Path

$vendorHeaders =
    @{
        Name = "glext.h";
        Source = "https://raw.githubusercontent.com/KhronosGroup/OpenGL-Registry/refs/heads/main/api/GL/glext.h";
        Target = "vendor\include\gl\glext.h"
    },
    @{
        Name = "khrplatform.h";
        Source = "https://registry.khronos.org/EGL/api/KHR/khrplatform.h";
        Target = "vendor\include\KHR\khrplatform.h"
    },
    @{
        Name = "wglext.h";
        Source = "https://raw.githubusercontent.com/KhronosGroup/OpenGL-Registry/refs/heads/main/api/GL/wglext.h";
        Target = "vendor\include\gl\wglext.h"
    }

Add-Type -AssemblyName System.Net.Http
$client = [System.Net.Http.HttpClient]::new()

foreach ($file in $vendorHeaders) {
    $name = $file.Name
    $source = $file.Source
    $targetPath = Join-Path $repoPath $file.Target
    $targetDir = Split-Path $targetPath -Parent

    New-Item -ItemType Directory -Path $targetDir -Force | Out-Null

    Write-Host "Downloading $name"
    Write-Host "    URL: $targetPath"
    Write-Host "    Saving to $targetPath"

    $response = $client.GetAsync($source, [System.Net.Http.HttpCompletionOption]::ResponseHeadersRead).Result
    $stream = $response.Content.ReadAsStreamAsync().Result
    $fileStream = [System.IO.File]::Create($targetPath)
    $stream.CopyTo($fileStream)

    $fileStream.Close()
    $stream.Close()
}
