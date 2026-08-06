import 'package:flutter/material.dart';

void main() {
  runApp(const ResponsiveOrientationDemo());
}

class ResponsiveOrientationDemo extends StatelessWidget {
  const ResponsiveOrientationDemo({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: "Responsive Orientation Demo",
      theme: ThemeData(
        primarySwatch: Colors.indigo,
      ),
      home: const HomePage(),
    );
  }
}

class GalleryItem {
  final String title;
  final String description;
  final IconData icon;

  GalleryItem({
    required this.title,
    required this.description,
    required this.icon,
  });
}

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  final List<GalleryItem> items = const [
    GalleryItem(
      title: "Camera",
      description: "Capture beautiful moments.",
      icon: Icons.camera_alt,
    ),
    GalleryItem(
      title: "Music",
      description: "Enjoy your favorite songs.",
      icon: Icons.music_note,
    ),
    GalleryItem(
      title: "Travel",
      description: "Explore amazing places.",
      icon: Icons.flight,
    ),
    GalleryItem(
      title: "Books",
      description: "Read inspiring stories.",
      icon: Icons.book,
    ),
    GalleryItem(
      title: "Food",
      description: "Taste delicious recipes.",
      icon: Icons.restaurant,
    ),
    GalleryItem(
      title: "Fitness",
      description: "Stay healthy and active.",
      icon: Icons.fitness_center,
    ),
  ];

  @override
  Widget build(BuildContext context) {
    double width = MediaQuery.of(context).size.width;
    Orientation orientation = MediaQuery.of(context).orientation;

    String category = width < 600
        ? "Mobile"
        : width < 1024
            ? "Tablet"
            : "Desktop";

    return LayoutBuilder(
      builder: (context, constraints) {
        Widget body;

        if (constraints.maxWidth < 600) {
          body = _buildMobileLayout(context);
        } else if (constraints.maxWidth < 1024) {
          body = _buildTabletLayout(context);
        } else {
          body = _buildDesktopLayout(context);
        }

        return Scaffold(
          appBar: AppBar(
            title: const Text("Responsive Gallery"),
            centerTitle: true,
          ),
          body: Column(
            children: [
              Expanded(child: body),

              // Footer
              Container(
                width: double.infinity,
                color: Colors.indigo.shade100,
                padding: const EdgeInsets.all(12),
                child: Text(
                  "Width: ${width.toStringAsFixed(0)} px   |   Device: $category   |   Orientation: ${orientation.name}",
                  textAlign: TextAlign.center,
                  style: const TextStyle(
                    fontWeight: FontWeight.bold,
                  ),
                ),
              )
            ],
          ),
        );
      },
    );
  }

  // ---------------- MOBILE ----------------

  Widget _buildMobileLayout(BuildContext context) {
    return OrientationBuilder(
      builder: (context, orientation) {
        if (orientation == Orientation.portrait) {
          return ListView.builder(
            padding: const EdgeInsets.all(12),
            itemCount: items.length,
            itemBuilder: (context, index) {
              return _buildCard(items[index]);
            },
          );
        } else {
          return ListView.builder(
            scrollDirection: Axis.horizontal,
            padding: const EdgeInsets.all(12),
            itemCount: items.length,
            itemBuilder: (context, index) {
              return SizedBox(
                width: 250,
                child: _buildCard(items[index]),
              );
            },
          );
        }
      },
    );
  }

  // ---------------- TABLET ----------------

  Widget _buildTabletLayout(BuildContext context) {
    return OrientationBuilder(
      builder: (context, orientation) {
        double padding = orientation == Orientation.portrait ? 12 : 24;

        return Padding(
          padding: EdgeInsets.all(padding),
          child: GridView.builder(
            itemCount: items.length,
            gridDelegate:
                const SliverGridDelegateWithFixedCrossAxisCount(
              crossAxisCount: 2,
              crossAxisSpacing: 20,
              mainAxisSpacing: 20,
              childAspectRatio: 1.2,
            ),
            itemBuilder: (context, index) {
              return _buildCard(
                items[index],
                fontSize:
                    orientation == Orientation.portrait ? 18 : 22,
              );
            },
          ),
        );
      },
    );
  }

  // ---------------- DESKTOP ----------------

  Widget _buildDesktopLayout(BuildContext context) {
    return Row(
      children: [
        NavigationRail(
          selectedIndex: 0,
          destinations: const [
            NavigationRailDestination(
              icon: Icon(Icons.home),
              label: Text("Home"),
            ),
            NavigationRailDestination(
              icon: Icon(Icons.photo),
              label: Text("Gallery"),
            ),
            NavigationRailDestination(
              icon: Icon(Icons.settings),
              label: Text("Settings"),
            ),
          ],
        ),
        const VerticalDivider(width: 1),
        Expanded(
          child: Padding(
            padding: const EdgeInsets.all(20),
            child: GridView.builder(
              itemCount: items.length,
              gridDelegate:
                  const SliverGridDelegateWithFixedCrossAxisCount(
                crossAxisCount: 3,
                crossAxisSpacing: 20,
                mainAxisSpacing: 20,
                childAspectRatio: 1.3,
              ),
              itemBuilder: (context, index) {
                return _buildCard(
                  items[index],
                  fontSize: 22,
                );
              },
            ),
          ),
        ),
      ],
    );
  }

  // ---------------- CARD ----------------

  Widget _buildCard(
    GalleryItem item, {
    double fontSize = 18,
  }) {
    return Card(
      elevation: 5,
      margin: const EdgeInsets.all(8),
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(15),
      ),
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Icon(
              item.icon,
              size: 60,
              color: Colors.indigo,
            ),
            const SizedBox(height: 15),
            Text(
              item.title,
              style: TextStyle(
                fontSize: fontSize,
                fontWeight: FontWeight.bold,
              ),
            ),
            const SizedBox(height: 10),
            Text(
              item.description,
              textAlign: TextAlign.center,
              style: TextStyle(
                fontSize: fontSize - 4,
              ),
            ),
          ],
        ),
      ),
    );
  }
}