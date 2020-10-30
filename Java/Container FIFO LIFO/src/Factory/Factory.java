package Factory;

import Container.Container;

public interface Factory {
    Container createContainer(Strategy strategy);
}
