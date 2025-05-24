# Get all .txt files in the current directory
$txtFiles = Get-ChildItem -Filter "*.txt"

# Initialize an array to store the output strings
$outputLines = @()

# Loop through each .txt file
foreach ($file in $txtFiles) {
    # Get the content of the file and count the lines
    $lineCount = (Get-Content $file.FullName).Count

    # Create the output string
    $outputString = "$($file.Name): $lineCount"

    # Add the string to the output array
    $outputLines += $outputString
}

# Output the results to count.txt
Set-Content -Path "count.txt" -Value $outputLines

Write-Host "Processing complete. Results saved to count.txt"
