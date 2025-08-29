<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Cub3D Map Parser</title>
    <style>
        body {
            font-family: 'Courier New', monospace;
            background-color: #1a1a2e;
            color: #e6e6e6;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        header {
            text-align: center;
            margin-bottom: 30px;
            border-bottom: 2px solid #4cc9f0;
            padding-bottom: 10px;
        }
        h1 {
            color: #4cc9f0;
            text-shadow: 0 0 5px rgba(76, 201, 240, 0.5);
        }
        .container {
            display: flex;
            gap: 20px;
            flex-wrap: wrap;
        }
        .panel {
            flex: 1;
            min-width: 300px;
            background-color: #16213e;
            border-radius: 8px;
            padding: 15px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.3);
        }
        h2 {
            color: #4cc9f0;
            border-bottom: 1px solid #4cc9f0;
            padding-bottom: 5px;
        }
        .input-area {
            width: 100%;
            min-height: 200px;
            background-color: #0f3460;
            color: #e6e6e6;
            border: 1px solid #4cc9f0;
            border-radius: 4px;
            padding: 10px;
            font-family: 'Courier New', monospace;
            margin-bottom: 15px;
        }
        button {
            background-color: #4cc9f0;
            color: #1a1a2e;
            border: none;
            padding: 10px 15px;
            border-radius: 4px;
            cursor: pointer;
            font-weight: bold;
            transition: background-color 0.3s;
        }
        button:hover {
            background-color: #2b9fc9;
        }
        .result {
            margin-top: 15px;
            padding: 10px;
            border-radius: 4px;
            min-height: 100px;
            background-color: #0f3460;
            white-space: pre-wrap;
            font-family: 'Courier New', monospace;
        }
        .success {
            color: #4ade80;
        }
        .error {
            color: #f87171;
        }
        .map-display {
            line-height: 1;
            letter-spacing: 2px;
            font-family: 'Courier New', monospace;
            font-size: 14px;
        }
        .player {
            color: #ff0000;
            font-weight: bold;
        }
        .wall {
            color: #4cc9f0;
        }
        .space {
            color: #666;
        }
        .texture {
            color: #f0e68c;
        }
        .color {
            color: #98fb98;
        }
    </style>
</head>
<body>
    <header>
        <h1>Cub3D Map Parser</h1>
        <p>Validate and parse your cub3D map files according to the project specifications</p>
    </header>

    <div class="container">
        <div class="panel">
            <h2>Input Map File</h2>
            <textarea id="mapInput" class="input-area">NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,3,090

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
111111111 1111111 111111111111</textarea>
            <button id="parseBtn">Parse Map</button>
        </div>

        <div class="panel">
            <h2>Parsing Results</h2>
            <div id="results" class="result">Results will appear here...</div>
        </div>

        <div class="panel">
            <h2>Extracted Information</h2>
            <div id="extractedInfo" class="result">Extracted information will appear here...</div>
        </div>
    </div>

    <script>
        document.getElementById('parseBtn').addEventListener('click', function() {
            const mapText = document.getElementById('mapInput').value;
            const results = parseCubFile(mapText);
            
            // Display results
            const resultsDiv = document.getElementById('results');
            if (results.isValid) {
                resultsDiv.innerHTML = `<span class="success">✓ Map is valid!</span>\n\n`;
            } else {
                resultsDiv.innerHTML = `<span class="error">✗ Map is invalid:</span>\n${results.errors.join('\n')}\n\n`;
            }
            
            // Display extracted information
            const infoDiv = document.getElementById('extractedInfo');
            infoDiv.innerHTML = '';
            
            // Display textures
            infoDiv.innerHTML += '<h3>Textures:</h3>';
            for (const [key, value] of Object.entries(results.textures)) {
                infoDiv.innerHTML += `<span class="texture">${key}: ${value}</span><br>`;
            }
            
            // Display colors
            infoDiv.innerHTML += '<h3>Colors:</h3>';
            infoDiv.innerHTML += `<span class="color">Floor: RGB(${results.colors.F.join(', ')})</span><br>`;
            infoDiv.innerHTML += `<span class="color">Ceiling: RGB(${results.colors.C.join(', ')})</span><br>`;
            
            // Display map
            infoDiv.innerHTML += '<h3>Map:</h3>';
            infoDiv.innerHTML += '<div class="map-display">';
            for (let y = 0; y < results.map.length; y++) {
                for (let x = 0; x < results.map[y].length; x++) {
                    const cell = results.map[y][x];
                    if (['N', 'S', 'E', 'W'].includes(cell)) {
                        infoDiv.innerHTML += `<span class="player">${cell}</span>`;
                    } else if (cell === '1') {
                        infoDiv.innerHTML += `<span class="wall">${cell}</span>`;
                    } else if (cell === '0') {
                        infoDiv.innerHTML += `<span class="space">${cell}</span>`;
                    } else {
                        infoDiv.innerHTML += cell;
                    }
                }
                infoDiv.innerHTML += '<br>';
            }
            infoDiv.innerHTML += '</div>';
            
            // Display player info if found
            if (results.player) {
                infoDiv.innerHTML += `<h3>Player:</h3>`;
                infoDiv.innerHTML += `Position: (${results.player.x}, ${results.player.y})<br>`;
                infoDiv.innerHTML += `Direction: ${results.player.direction}<br>`;
            }
        });

        function parseCubFile(content) {
            const lines = content.split('\n');
            const result = {
                isValid: true,
                errors: [],
                textures: {},
                colors: { F: null, C: null },
                map: [],
                player: null
            };
            
            let parsingMap = false;
            let mapLines = [];
            
            for (let i = 0; i < lines.length; i++) {
                const line = lines[i].trim();
                
                // Skip empty lines before map parsing
                if (!parsingMap && line === '') continue;
                
                // Check if we've started parsing the map
                if (!parsingMap && /^[01NSEW\s]+$/.test(line)) {
                    parsingMap = true;
                }
                
                if (parsingMap) {
                    // We're in the map section
                    if (line !== '') {
                        mapLines.push(line);
                    }
                } else {
                    // We're in the texture/color section
                    if (line.startsWith('NO ')) {
                        result.textures.NO = line.substring(3).trim();
                    } else if (line.startsWith('SO ')) {
                        result.textures.SO = line.substring(3).trim();
                    } else if (line.startsWith('WE ')) {
                        result.textures.WE = line.substring(3).trim();
                    } else if (line.startsWith('EA ')) {
                        result.textures.EA = line.substring(3).trim();
                    } else if (line.startsWith('F ')) {
                        const colorParts = line.substring(2).trim().split(',');
                        if (colorParts.length !== 3) {
                            result.isValid = false;
                            result.errors.push(`Invalid floor color format on line ${i+1}`);
                        } else {
                            result.colors.F = colorParts.map(part => parseInt(part.trim()));
                            if (result.colors.F.some(isNaN)) {
                                result.isValid = false;
                                result.errors.push(`Invalid floor color values on line ${i+1}`);
                            }
                        }
                    } else if (line.startsWith('C ')) {
                        const colorParts = line.substring(2).trim().split(',');
                        if (colorParts.length !== 3) {
                            result.isValid = false;
                            result.errors.push(`Invalid ceiling color format on line ${i+1}`);
                        } else {
                            result.colors.C = colorParts.map(part => parseInt(part.trim()));
                            if (result.colors.C.some(isNaN)) {
                                result.isValid = false;
                                result.errors.push(`Invalid ceiling color values on line ${i+1}`);
                            }
                        }
                    } else if (line !== '') {
                        result.isValid = false;
                        result.errors.push(`Unknown directive on line ${i+1}: ${line}`);
                    }
                }
            }
            
            // Validate that we have all required textures and colors
            const requiredTextures = ['NO', 'SO', 'WE', 'EA'];
            for (const texture of requiredTextures) {
                if (!result.textures[texture]) {
                    result.isValid = false;
                    result.errors.push(`Missing required texture: ${texture}`);
                }
            }
            
            if (!result.colors.F) {
                result.isValid = false;
                result.errors.push('Missing floor color');
            }
            
            if (!result.colors.C) {
                result.isValid = false;
                result.errors.push('Missing ceiling color');
            }
            
            // Parse the map
            if (mapLines.length === 0) {
                result.isValid = false;
                result.errors.push('Map is empty');
                return result;
            }
            
            // Find the maximum line length to normalize the map
            const maxLength = Math.max(...mapLines.map(line => line.length));
            
            // Create the map grid
            for (let i = 0; i < mapLines.length; i++) {
                const row = [];
                for (let j = 0; j < maxLength; j++) {
                    if (j >= mapLines[i].length) {
                        row.push(' ');
                    } else {
                        const char = mapLines[i][j];
                        if (['0', '1', 'N', 'S', 'E', 'W', ' '].includes(char)) {
                            row.push(char);
                            
                            // Check for player position
                            if (['N', 'S', 'E', 'W'].includes(char)) {
                                if (result.player) {
                                    result.isValid = false;
                                    result.errors.push(`Multiple player positions found at (${j}, ${i})`);
                                } else {
                                    result.player = {
                                        x: j,
                                        y: i,
                                        direction: char
                                    };
                                }
                            }
                        } else {
                            result.isValid = false;
                            result.errors.push(`Invalid character '${char}' in map at position (${j}, ${i})`);
                        }
                    }
                }
                result.map.push(row);
            }
            
            // Check if we have a player
            if (!result.player) {
                result.isValid = false;
                result.errors.push('No player starting position found');
            }
            
            // Validate that the map is surrounded by walls
            if (result.isValid) {
                // Check top and bottom borders
                for (let x = 0; x < result.map[0].length; x++) {
                    if (result.map[0][x] !== '1' && result.map[0][x] !== ' ') {
                        result.isValid = false;
                        result.errors.push(`Map is not closed at top border, position (${x}, 0)`);
                    }
                    
                    if (result.map[result.map.length - 1][x] !== '1' && result.map[result.map.length - 1][x] !== ' ') {
                        result.isValid = false;
                        result.errors.push(`Map is not closed at bottom border, position (${x}, ${result.map.length - 1})`);
                    }
                }
                
                // Check left and right borders
                for (let y = 0; y < result.map.length; y++) {
                    if (result.map[y][0] !== '1' && result.map[y][0] !== ' ') {
                        result.isValid = false;
                        result.errors.push(`Map is not closed at left border, position (0, ${y})`);
                    }
                    
                    if (result.map[y][result.map[y].length - 1] !== '1' && result.map[y][result.map[y].length - 1] !== ' ') {
                        result.isValid = false;
                        result.errors.push(`Map is not closed at right border, position (${result.map[y].length - 1}, ${y})`);
                    }
                }
                
                // Check that all spaces inside are accessible (flood fill algorithm would be better,
                // but for this demo we'll do a simple check)
                for (let y = 1; y < result.map.length - 1; y++) {
                    for (let x = 1; x < result.map[y].length - 1; x++) {
                        if (result.map[y][x] === '0' || ['N', 'S', 'E', 'W'].includes(result.map[y][x])) {
                            // Check if this position is adjacent to empty space (which would mean the map is not closed)
                            if (result.map[y-1][x] === ' ' || result.map[y+1][x] === ' ' || 
                                result.map[y][x-1] === ' ' || result.map[y][x+1] === ' ') {
                                result.isValid = false;
                                result.errors.push(`Map is not closed at position (${x}, ${y})`);
                            }
                        }
                    }
                }
            }
            
            return result;
        }
    </script>
</body>
</html>