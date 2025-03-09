# Duo-Mode Multi-Agent Autonomous Agent Simulation Platform  

## Overview  
This project aims to develop a **Duo-Mode multi-agent autonomous agent simulation platform** in virtual environment and agent behavior control. The system will demonstrate real-time agent movement, interactions, and decision-making in a virtual environment, utilizing sensors, collision handling, and user inputs for seamless simulation.  


## Objectives  

### 1. Automated Agent Behavior in a Virtual Environment  
- Implement **autonomous agent movement** with realistic physics-based controls.  
- Agents will navigate the environment, responding to obstacles, and interactions.  
- Pathfinding and decision-making will be integrated based on predefined logic.  

### 2. Multi-Agent Interaction via Sensors, Collision Handling, and User Input  
- Utilize **sensors and collision handlers** to enable realistic agent interactions.  
- Implement **keyboard and input-based controls** for manual and autonomous movement.  
- Enable **agent-to-agent interactions**, such as competitive behavior.  

### 3. Dual Control Modes
- **Autonomous Mode** (Default):
  - Automatic obstacle avoidance
  - Forward movement in clear paths
  - Random direction selection when avoiding obstacles
  - Red block detection and response

- **Manual Control Mode**:
  - Toggle with 'M' key
  - Arrow key controls:
    - ↑: Move forward (10.0 speed)
    - ↓: Move backward (-5.0 speed)
    - ←: Rotate left 
    - →: Rotate right 
  - Return to autonomous mode with 'Q' key
  - Collision prevention system active

### 2. Collision and Obstacle Handling
- Proximity detection 
- Automatic collision avoidance in both modes
- Red block detection and response
- Dynamic velocity adjustment near obstacles


## Technical Stack  
- **Simulation Engine:** Enviro (for physics, movement, and multi-agent control)   
- **Data Format:** JSON-based world description and configuration  


## Implementation Features

### Agent Behavior
- **State Machine Architecture**: Agents utilize a three-state behavior system:
  - `MovingForward`: Default state where agents move forward at a constant velocity
  - `Rotating`: Triggered when obstacles are detected, allowing agents to find new paths
  - `Stopped`: Activated when specific conditions are met (e.g., detecting red blocks)

### Sensor Integration
- **Proximity Detection**: Agents use sensors to detect obstacles within 40 units
- **Color Recognition**: Implemented red block detection capability
  - Agents automatically stop when encountering red objects within 30 units
- **Dynamic Obstacle Avoidance**: 
  - Rotation triggered when obstacles are detected within 40 units
  - Returns to forward movement when clear path is detected (sensor value > 140)

### Agent Controller
- **Randomized Behavior**: Implements random rotation direction selection
- **Event-Based State Transitions**: Uses unique tick names per agent instance
- **Velocity Control**: Precise tracking of both linear and angular velocities
- **Collision Prevention**: Built-in obstacle avoidance behavior

## Usage
To run the simulation:
1. Start the Docker container:
   ```bash
   docker run -p8080:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.5 bash
   ```

2. Build and run the project:
   ```bash
   make
   esm start
   enviro
   ```

3. Controls:
   - **Mode Switching**:
     - Press 'M' to enter manual control mode
     - Press 'Q' to return to autonomous mode
   
   - **Autonomous Mode**:
     - Agents will automatically:
       - Move forward in open spaces
       - Avoid obstacles by rotating
       - Stop when encountering red blocks
   
   - **User-Controlled Mode**:
     - `←`: Move left
     - `→`: Move right
     - `↑`: Move up
     - `↓`: Move down

4. Access the simulation:
   - Open a web browser and navigate to `http://localhost:8080`
   - The agent will start in autonomous mode by default

   


### Simulation Environment
![Simulation Environment](/project/result/result1.png)
*Main simulation environment showing agents and obstacles*

### Autonomous Navigation
![Autonomous Navigation](/project/result/result2.png)
*Agent demonstrating autonomous navigation and obstacle avoidance*
