# LLM-based Multi-Agent Autonomous Agent Simulation Platform  

## Overview  
This project aims to develop a **multi-agent autonomous simulation platform** in dynamic environment and agent behavior control. The system will demonstrate real-time agent movement, interactions, and decision-making in a virtual environment, utilizing sensors, collision handling, and user inputs for seamless simulation.  

## Objectives  

### 1. Automated Agent Behavior in a Dynamic Environment  
- Implement **autonomous agent movement** with realistic physics-based controls.  
- Agents will navigate the environment, responding to obstacles, and interactions.  
- Pathfinding and decision-making will be integrated based on predefined logic.  

### 2. Multi-Agent Interaction via Sensors, Collision Handling, and User Input  
- Utilize **sensors and collision handlers** to enable realistic agent interactions.  
- Implement **keyboard and input-based controls** for manual and autonomous movement.  
- Enable **agent-to-agent interactions**, such as competitive behavior.  


## Technical Stack  
- **Simulation Engine:** Enviro (for physics, movement, and multi-agent control)   
- **Data Format:** JSON-based world description and configuration  

## Expected Outcomes  
- A **fully interactive** multi-agent platform demonstrating **autonomous movement, decision-making, and real-time interactions**.  
- A **multi-user experience**, where players can control or observe agents in the dynamically generated environment.  
- A **procedurally generated simulation space**, allowing natural language commands to define the world and its agents.  

## Current Implementation Features

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
     - Press `T` to toggle between autonomous and user-controlled modes
   
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
   - You should see both autonomous and user-controlled agents in the environment
